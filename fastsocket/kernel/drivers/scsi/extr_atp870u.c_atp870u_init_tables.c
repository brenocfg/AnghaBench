#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct atp_unit {int* host_id; int* last_cmd; int** sp; TYPE_1__** id; int /*<<< orphan*/ *** quereq; scalar_t__* in_int; scalar_t__* in_snd; scalar_t__* quend; scalar_t__* quhd; scalar_t__* wide_id; scalar_t__* active_id; int /*<<< orphan*/  pdev; } ;
struct Scsi_Host {int /*<<< orphan*/  hostdata; } ;
struct TYPE_2__ {int devsp; int devtype; int /*<<< orphan*/ * curr_req; int /*<<< orphan*/  prd_bus; int /*<<< orphan*/  prdaddr; int /*<<< orphan*/  prd_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  atp870u_free_tables (struct Scsi_Host*) ; 
 int /*<<< orphan*/  pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int qcnt ; 

__attribute__((used)) static int atp870u_init_tables(struct Scsi_Host *host)
{
	struct atp_unit *atp_dev = (struct atp_unit *)&host->hostdata;
	int c,k;
	for(c=0;c < 2;c++) {
	   	for(k=0;k<16;k++) {
	   			atp_dev->id[c][k].prd_table = pci_alloc_consistent(atp_dev->pdev, 1024, &(atp_dev->id[c][k].prd_bus));
	   			if (!atp_dev->id[c][k].prd_table) {
	   				printk("atp870u_init_tables fail\n");
				atp870u_free_tables(host);
				return -ENOMEM;
			}
			atp_dev->id[c][k].prdaddr = atp_dev->id[c][k].prd_bus;
			atp_dev->id[c][k].devsp=0x20;
			atp_dev->id[c][k].devtype = 0x7f;
			atp_dev->id[c][k].curr_req = NULL;			   
	   	}
	   			
	   	atp_dev->active_id[c] = 0;
	   	atp_dev->wide_id[c] = 0;
	   	atp_dev->host_id[c] = 0x07;
	   	atp_dev->quhd[c] = 0;
	   	atp_dev->quend[c] = 0;
	   	atp_dev->last_cmd[c] = 0xff;
	   	atp_dev->in_snd[c] = 0;
	   	atp_dev->in_int[c] = 0;
	   	
	   	for (k = 0; k < qcnt; k++) {
	   		  atp_dev->quereq[c][k] = NULL;
	   	}	   		   
	   	for (k = 0; k < 16; k++) {
			   atp_dev->id[c][k].curr_req = NULL;
			   atp_dev->sp[c][k] = 0x04;
	   	}		   
	}
	return 0;
}