#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; scalar_t__ host_scribble; TYPE_1__* device; } ;
struct mscp {void (* done ) (struct scsi_cmnd*) ;struct scsi_cmnd* SCint; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
struct TYPE_5__ {int slot; int icm_address; int ogm_address; struct mscp* mscp; int /*<<< orphan*/  doorbell_address; int /*<<< orphan*/ * aborted; } ;
struct TYPE_4__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int FAILED ; 
 int LCL_DOORBELL_INTR (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int SYS_DOORBELL_INTR (int /*<<< orphan*/ ) ; 
 unsigned int ULTRASTOR_MAX_CMDS ; 
 TYPE_2__ config ; 
 int inb (int) ; 
 int /*<<< orphan*/  inl (int) ; 
 scalar_t__ isa_bus_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_virt_to_bus (struct mscp*) ; 
 int /*<<< orphan*/  log_ultrastor_abort (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  ultrastor_interrupt (int /*<<< orphan*/ *) ; 
 unsigned char xchgb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ultrastor_abort(struct scsi_cmnd *SCpnt)
{
#if ULTRASTOR_DEBUG & UD_ABORT
    char out[108];
    unsigned char icm_status = 0, ogm_status = 0;
    unsigned int icm_addr = 0, ogm_addr = 0;
#endif
    unsigned int mscp_index;
    unsigned char old_aborted;
    unsigned long flags;
    void (*done)(struct scsi_cmnd *);
    struct Scsi_Host *host = SCpnt->device->host;

    if(config.slot) 
      return FAILED;  /* Do not attempt an abort for the 24f */
      
    /* Simple consistency checking */
    if(!SCpnt->host_scribble)
      return FAILED;

    mscp_index = ((struct mscp *)SCpnt->host_scribble) - config.mscp;
    if (mscp_index >= ULTRASTOR_MAX_CMDS)
	panic("Ux4F aborting invalid MSCP");

#if ULTRASTOR_DEBUG & UD_ABORT
    if (config.slot)
      {
	int port0 = (config.slot << 12) | 0xc80;
	int i;
	unsigned long flags;
	
	spin_lock_irqsave(host->host_lock, flags);
	strcpy(out, "OGM %d:%x ICM %d:%x ports:  ");
	for (i = 0; i < 16; i++)
	  {
	    unsigned char p = inb(port0 + i);
	    out[28 + i * 3] = "0123456789abcdef"[p >> 4];
	    out[29 + i * 3] = "0123456789abcdef"[p & 15];
	    out[30 + i * 3] = ' ';
	  }
	out[28 + i * 3] = '\n';
	out[29 + i * 3] = 0;
	ogm_status = inb(port0 + 22);
	ogm_addr = (unsigned int)isa_bus_to_virt(inl(port0 + 23));
	icm_status = inb(port0 + 27);
	icm_addr = (unsigned int)isa_bus_to_virt(inl(port0 + 28));
	spin_unlock_irqrestore(host->host_lock, flags);
      }

    /* First check to see if an interrupt is pending.  I suspect the SiS
       chipset loses interrupts.  (I also suspect is mangles data, but
       one bug at a time... */
    if (config.slot ? inb(config.icm_address - 1) == 2 :
	(inb(SYS_DOORBELL_INTR(config.doorbell_address)) & 1))
      {
	printk("Ux4F: abort while completed command pending\n");
	
	spin_lock_irqsave(host->host_lock, flags);
	/* FIXME: Ewww... need to think about passing host around properly */
	ultrastor_interrupt(NULL);
	spin_unlock_irqrestore(host->host_lock, flags);
	return SUCCESS;
      }
#endif

    old_aborted = xchgb(DID_ABORT, &config.aborted[mscp_index]);

    /* aborted == 0xff is the signal that queuecommand has not yet sent
       the command.  It will notice the new abort flag and fail.  */
    if (old_aborted == 0xff)
	return SUCCESS;

    /* On 24F, send an abort MSCP request.  The adapter will interrupt
       and the interrupt handler will call done.  */
    if (config.slot && inb(config.ogm_address - 1) == 0)
      {
	unsigned long flags;

	spin_lock_irqsave(host->host_lock, flags);
	outl(isa_virt_to_bus(&config.mscp[mscp_index]), config.ogm_address);
	udelay(8);
	outb(0x80, config.ogm_address - 1);
	outb(0x2, LCL_DOORBELL_INTR(config.doorbell_address));
#if ULTRASTOR_DEBUG & UD_ABORT
	log_ultrastor_abort(&config, mscp_index);
	printk(out, ogm_status, ogm_addr, icm_status, icm_addr);
#endif
	spin_unlock_irqrestore(host->host_lock, flags);
	/* FIXME: add a wait for the abort to complete */
	return SUCCESS;
      }

#if ULTRASTOR_DEBUG & UD_ABORT
    log_ultrastor_abort(&config, mscp_index);
#endif

    /* Can't request a graceful abort.  Either this is not a 24F or
       the OGM is busy.  Don't free the command -- the adapter might
       still be using it.  Setting SCint = 0 causes the interrupt
       handler to ignore the command.  */

    /* FIXME - devices that implement soft resets will still be running
       the command after a bus reset.  We would probably rather leave
       the command in the queue.  The upper level code will automatically
       leave the command in the active state instead of requeueing it. ERY */

#if ULTRASTOR_DEBUG & UD_ABORT
    if (config.mscp[mscp_index].SCint != SCpnt)
	printk("abort: command mismatch, %p != %p\n",
	       config.mscp[mscp_index].SCint, SCpnt);
#endif
    if (config.mscp[mscp_index].SCint == NULL)
	return FAILED;

    if (config.mscp[mscp_index].SCint != SCpnt) panic("Bad abort");
    config.mscp[mscp_index].SCint = NULL;
    done = config.mscp[mscp_index].done;
    config.mscp[mscp_index].done = NULL;
    SCpnt->result = DID_ABORT << 16;
    
    /* Take the host lock to guard against scsi layer re-entry */
    done(SCpnt);

    /* Need to set a timeout here in case command never completes.  */
    return SUCCESS;
}