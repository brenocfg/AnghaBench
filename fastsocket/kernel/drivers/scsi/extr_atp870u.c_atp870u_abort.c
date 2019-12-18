#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {unsigned char cmd_len; unsigned int* cmnd; TYPE_1__* device; } ;
struct atp_unit {unsigned int* ioport; unsigned int* pciport; TYPE_2__** id; int /*<<< orphan*/ * in_snd; int /*<<< orphan*/ * quend; int /*<<< orphan*/ * quhd; int /*<<< orphan*/ * last_cmd; int /*<<< orphan*/ * working; } ;
struct Scsi_Host {int /*<<< orphan*/  hostdata; } ;
struct TYPE_4__ {scalar_t__ last_len; struct scsi_cmnd* curr_req; } ;
struct TYPE_3__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int SUCCESS ; 
 unsigned int inb (unsigned int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned char scmd_channel (struct scsi_cmnd*) ; 

__attribute__((used)) static int atp870u_abort(struct scsi_cmnd * SCpnt)
{
	unsigned char  j, k, c;
	struct scsi_cmnd *workrequ;
	unsigned int tmport;
	struct atp_unit *dev;	
	struct Scsi_Host *host;
	host = SCpnt->device->host;

	dev = (struct atp_unit *)&host->hostdata;
	c = scmd_channel(SCpnt);
	printk(" atp870u: abort Channel = %x \n", c);
	printk("working=%x last_cmd=%x ", dev->working[c], dev->last_cmd[c]);
	printk(" quhdu=%x quendu=%x ", dev->quhd[c], dev->quend[c]);
	tmport = dev->ioport[c];
	for (j = 0; j < 0x18; j++) {
		printk(" r%2x=%2x", j, inb(tmport++));
	}
	tmport += 0x04;
	printk(" r1c=%2x", inb(tmport));
	tmport += 0x03;
	printk(" r1f=%2x in_snd=%2x ", inb(tmport), dev->in_snd[c]);
	tmport= dev->pciport[c];
	printk(" d00=%2x", inb(tmport));
	tmport += 0x02;
	printk(" d02=%2x", inb(tmport));
	for(j=0;j<16;j++) {
	   if (dev->id[c][j].curr_req != NULL) {
		workrequ = dev->id[c][j].curr_req;
		printk("\n que cdb= ");
		for (k=0; k < workrequ->cmd_len; k++) {
		    printk(" %2x ",workrequ->cmnd[k]);
		}
		printk(" last_lenu= %x ",(unsigned int)dev->id[c][j].last_len);
	   }
	}
	return SUCCESS;
}