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
struct tape_request {size_t op; } ;
struct tape_device {int /*<<< orphan*/  cdev_id; } ;
struct TYPE_3__ {unsigned int dstat; unsigned int cstat; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {scalar_t__ ecw; TYPE_2__ scsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,unsigned int,...) ; 
 char** tape_op_verbose ; 

void
tape_dump_sense_dbf(struct tape_device *device, struct tape_request *request,
		    struct irb *irb)
{
	unsigned int *sptr;
	const char* op;

	if (request != NULL)
		op = tape_op_verbose[request->op];
	else
		op = "---";
	DBF_EVENT(3, "DSTAT : %02x   CSTAT: %02x\n",
		  irb->scsw.cmd.dstat, irb->scsw.cmd.cstat);
	DBF_EVENT(3, "DEVICE: %08x OP\t: %s\n", device->cdev_id, op);
	sptr = (unsigned int *) irb->ecw;
	DBF_EVENT(3, "%08x %08x\n", sptr[0], sptr[1]);
	DBF_EVENT(3, "%08x %08x\n", sptr[2], sptr[3]);
	DBF_EVENT(3, "%08x %08x\n", sptr[4], sptr[5]);
	DBF_EVENT(3, "%08x %08x\n", sptr[6], sptr[7]);
}