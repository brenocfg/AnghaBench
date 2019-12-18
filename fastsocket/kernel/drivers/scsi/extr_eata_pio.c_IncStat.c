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
struct scsi_pointer {unsigned int ptr; unsigned int this_residual; scalar_t__ buffers_residual; TYPE_1__* buffer; scalar_t__ Status; } ;
struct TYPE_2__ {unsigned int length; } ;

/* Variables and functions */
 unsigned int sg_virt (TYPE_1__*) ; 

__attribute__((used)) static void IncStat(struct scsi_pointer *SCp, unsigned int Increment)
{
	SCp->ptr += Increment;
	if ((SCp->this_residual -= Increment) == 0) {
		if ((--SCp->buffers_residual) == 0)
			SCp->Status = 0;
		else {
			SCp->buffer++;
			SCp->ptr = sg_virt(SCp->buffer);
			SCp->this_residual = SCp->buffer->length;
		}
	}
}