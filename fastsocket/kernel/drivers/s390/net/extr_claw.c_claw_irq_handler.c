#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int cstat; int dstat; int /*<<< orphan*/  cpa; } ;
struct TYPE_13__ {TYPE_4__ cmd; } ;
struct irb {TYPE_5__ scsw; int /*<<< orphan*/ * ecw; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_errors; } ;
struct claw_privbk {struct chbk* channel; TYPE_1__ stats; struct claw_env* p_env; } ;
struct claw_env {int /*<<< orphan*/  adapter_name; int /*<<< orphan*/  host_name; } ;
struct TYPE_15__ {unsigned long data; int /*<<< orphan*/  expires; void* function; } ;
struct chbk {int last_dstat; int claw_state; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  flag_a; int /*<<< orphan*/  IO_active; TYPE_6__* irb; TYPE_7__ timer; int /*<<< orphan*/  flag; int /*<<< orphan*/  wait; int /*<<< orphan*/  devno; scalar_t__ ndev; struct ccw_device* cdev; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int stctl; int dstat; int cstat; } ;
struct TYPE_11__ {TYPE_2__ cmd; } ;
struct TYPE_14__ {int* ecw; TYPE_3__ scsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_BH_ACTIVE ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLAW_READ ; 
#define  CLAW_START_HALT_IO 131 
#define  CLAW_START_READ 130 
#define  CLAW_START_WRITE 129 
#define  CLAW_STOP 128 
 int /*<<< orphan*/  CLAW_WRITE ; 
 int DEV_STAT_UNIT_CHECK ; 
 int DEV_STAT_UNIT_EXCEP ; 
 int HZ ; 
 int /*<<< orphan*/  LOCK_NO ; 
 size_t READ ; 
 int SCHN_STAT_PCI ; 
 int SCSW_STCTL_ALERT_STATUS ; 
 int SCSW_STCTL_SEC_STATUS ; 
 int SCSW_STCTL_STATUS_PEND ; 
 int /*<<< orphan*/  SYSTEM_VALIDATE_REQUEST ; 
 int /*<<< orphan*/  TB_RETRY ; 
 int /*<<< orphan*/  TB_TX ; 
 size_t WRITE ; 
 int /*<<< orphan*/  add_timer (TYPE_7__*) ; 
 int /*<<< orphan*/  ccw_check_unit_check (struct chbk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  claw_clear_busy (struct net_device*) ; 
 int /*<<< orphan*/  claw_clearbit_busy (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  claw_send_control (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  claw_strt_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  claw_test_and_setbit_busy (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  claw_write_next (struct chbk*) ; 
 scalar_t__ claw_write_retry ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,void*) ; 
 struct claw_privbk* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  init_timer (TYPE_7__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,struct irb*,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  trace ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
claw_irq_handler(struct ccw_device *cdev,
	unsigned long intparm, struct irb *irb)
{
        struct chbk *p_ch = NULL;
        struct claw_privbk *privptr = NULL;
        struct net_device *dev = NULL;
        struct claw_env  *p_env;
        struct chbk *p_ch_r=NULL;

	CLAW_DBF_TEXT(4, trace, "clawirq");
        /* Bypass all 'unsolicited interrupts' */
	privptr = dev_get_drvdata(&cdev->dev);
	if (!privptr) {
		dev_warn(&cdev->dev, "An uninitialized CLAW device received an"
			" IRQ, c-%02x d-%02x\n",
			irb->scsw.cmd.cstat, irb->scsw.cmd.dstat);
		CLAW_DBF_TEXT(2, trace, "badirq");
                return;
        }

	/* Try to extract channel from driver data. */
	if (privptr->channel[READ].cdev == cdev)
		p_ch = &privptr->channel[READ];
	else if (privptr->channel[WRITE].cdev == cdev)
		p_ch = &privptr->channel[WRITE];
	else {
		dev_warn(&cdev->dev, "The device is not a CLAW device\n");
		CLAW_DBF_TEXT(2, trace, "badchan");
		return;
	}
	CLAW_DBF_TEXT_(4, trace, "IRQCH=%d", p_ch->flag);

	dev = (struct net_device *) (p_ch->ndev);
        p_env=privptr->p_env;

	/* Copy interruption response block. */
	memcpy(p_ch->irb, irb, sizeof(struct irb));

	/* Check for good subchannel return code, otherwise info message */
	if (irb->scsw.cmd.cstat && !(irb->scsw.cmd.cstat & SCHN_STAT_PCI)) {
		dev_info(&cdev->dev,
			"%s: subchannel check for device: %04x -"
			" Sch Stat %02x  Dev Stat %02x CPA - %04x\n",
                        dev->name, p_ch->devno,
			irb->scsw.cmd.cstat, irb->scsw.cmd.dstat,
			irb->scsw.cmd.cpa);
		CLAW_DBF_TEXT(2, trace, "chanchk");
                /* return; */
        }

        /* Check the reason-code of a unit check */
	if (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK)
                ccw_check_unit_check(p_ch, irb->ecw[0]);

        /* State machine to bring the connection up, down and to restart */
	p_ch->last_dstat = irb->scsw.cmd.dstat;

        switch (p_ch->claw_state) {
	case CLAW_STOP:/* HALT_IO by claw_release (halt sequence) */
		if (!((p_ch->irb->scsw.cmd.stctl & SCSW_STCTL_SEC_STATUS) ||
		(p_ch->irb->scsw.cmd.stctl == SCSW_STCTL_STATUS_PEND) ||
		(p_ch->irb->scsw.cmd.stctl ==
		(SCSW_STCTL_ALERT_STATUS | SCSW_STCTL_STATUS_PEND))))
			return;
		wake_up(&p_ch->wait);   /* wake up claw_release */
		CLAW_DBF_TEXT(4, trace, "stop");
		return;
	case CLAW_START_HALT_IO: /* HALT_IO issued by claw_open  */
		if (!((p_ch->irb->scsw.cmd.stctl & SCSW_STCTL_SEC_STATUS) ||
		(p_ch->irb->scsw.cmd.stctl == SCSW_STCTL_STATUS_PEND) ||
		(p_ch->irb->scsw.cmd.stctl ==
		(SCSW_STCTL_ALERT_STATUS | SCSW_STCTL_STATUS_PEND)))) {
			CLAW_DBF_TEXT(4, trace, "haltio");
			return;
		}
		if (p_ch->flag == CLAW_READ) {
			p_ch->claw_state = CLAW_START_READ;
			wake_up(&p_ch->wait); /* wake claw_open (READ)*/
		} else if (p_ch->flag == CLAW_WRITE) {
			p_ch->claw_state = CLAW_START_WRITE;
			/*      send SYSTEM_VALIDATE                    */
			claw_strt_read(dev, LOCK_NO);
			claw_send_control(dev,
				SYSTEM_VALIDATE_REQUEST,
				0, 0, 0,
				p_env->host_name,
				p_env->adapter_name);
		} else {
			dev_warn(&cdev->dev, "The CLAW device received"
				" an unexpected IRQ, "
				"c-%02x d-%02x\n",
				irb->scsw.cmd.cstat,
				irb->scsw.cmd.dstat);
			return;
			}
		CLAW_DBF_TEXT(4, trace, "haltio");
		return;
	case CLAW_START_READ:
		CLAW_DBF_TEXT(4, trace, "ReadIRQ");
		if (p_ch->irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) {
			clear_bit(0, (void *)&p_ch->IO_active);
			if ((p_ch->irb->ecw[0] & 0x41) == 0x41 ||
			    (p_ch->irb->ecw[0] & 0x40) == 0x40 ||
			    (p_ch->irb->ecw[0])        == 0) {
				privptr->stats.rx_errors++;
				dev_info(&cdev->dev,
					"%s: Restart is required after remote "
					"side recovers \n",
					dev->name);
			}
			CLAW_DBF_TEXT(4, trace, "notrdy");
			return;
		}
		if ((p_ch->irb->scsw.cmd.cstat & SCHN_STAT_PCI) &&
			(p_ch->irb->scsw.cmd.dstat == 0)) {
			if (test_and_set_bit(CLAW_BH_ACTIVE,
				(void *)&p_ch->flag_a) == 0)
				tasklet_schedule(&p_ch->tasklet);
			else
				CLAW_DBF_TEXT(4, trace, "PCINoBH");
			CLAW_DBF_TEXT(4, trace, "PCI_read");
			return;
		}
		if (!((p_ch->irb->scsw.cmd.stctl & SCSW_STCTL_SEC_STATUS) ||
		 (p_ch->irb->scsw.cmd.stctl == SCSW_STCTL_STATUS_PEND) ||
		 (p_ch->irb->scsw.cmd.stctl ==
		 (SCSW_STCTL_ALERT_STATUS | SCSW_STCTL_STATUS_PEND)))) {
			CLAW_DBF_TEXT(4, trace, "SPend_rd");
			return;
		}
		clear_bit(0, (void *)&p_ch->IO_active);
		claw_clearbit_busy(TB_RETRY, dev);
		if (test_and_set_bit(CLAW_BH_ACTIVE,
			(void *)&p_ch->flag_a) == 0)
			tasklet_schedule(&p_ch->tasklet);
		else
			CLAW_DBF_TEXT(4, trace, "RdBHAct");
		CLAW_DBF_TEXT(4, trace, "RdIRQXit");
		return;
	case CLAW_START_WRITE:
		if (p_ch->irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) {
			dev_info(&cdev->dev,
				"%s: Unit Check Occured in "
				"write channel\n", dev->name);
			clear_bit(0, (void *)&p_ch->IO_active);
			if (p_ch->irb->ecw[0] & 0x80) {
				dev_info(&cdev->dev,
					"%s: Resetting Event "
					"occurred:\n", dev->name);
				init_timer(&p_ch->timer);
				p_ch->timer.function =
					(void *)claw_write_retry;
				p_ch->timer.data = (unsigned long)p_ch;
				p_ch->timer.expires = jiffies + 10*HZ;
				add_timer(&p_ch->timer);
				dev_info(&cdev->dev,
					"%s: write connection "
					"restarting\n", dev->name);
			}
			CLAW_DBF_TEXT(4, trace, "rstrtwrt");
			return;
		}
		if (p_ch->irb->scsw.cmd.dstat & DEV_STAT_UNIT_EXCEP) {
			clear_bit(0, (void *)&p_ch->IO_active);
			dev_info(&cdev->dev,
				"%s: Unit Exception "
				"occurred in write channel\n",
				dev->name);
		}
		if (!((p_ch->irb->scsw.cmd.stctl & SCSW_STCTL_SEC_STATUS) ||
		(p_ch->irb->scsw.cmd.stctl == SCSW_STCTL_STATUS_PEND) ||
		(p_ch->irb->scsw.cmd.stctl ==
		(SCSW_STCTL_ALERT_STATUS | SCSW_STCTL_STATUS_PEND)))) {
			CLAW_DBF_TEXT(4, trace, "writeUE");
			return;
		}
		clear_bit(0, (void *)&p_ch->IO_active);
		if (claw_test_and_setbit_busy(TB_TX, dev) == 0) {
			claw_write_next(p_ch);
			claw_clearbit_busy(TB_TX, dev);
			claw_clear_busy(dev);
		}
		p_ch_r = (struct chbk *)&privptr->channel[READ];
		if (test_and_set_bit(CLAW_BH_ACTIVE,
			(void *)&p_ch_r->flag_a) == 0)
			tasklet_schedule(&p_ch_r->tasklet);
		CLAW_DBF_TEXT(4, trace, "StWtExit");
		return;
	default:
		dev_warn(&cdev->dev,
			"The CLAW device for %s received an unexpected IRQ\n",
			 dev->name);
		CLAW_DBF_TEXT(2, trace, "badIRQ");
		return;
        }

}