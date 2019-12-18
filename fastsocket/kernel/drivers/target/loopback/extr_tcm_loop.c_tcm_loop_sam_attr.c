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
struct scsi_cmnd {int tag; TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ tagged_supported; } ;

/* Variables and functions */
#define  HEAD_OF_QUEUE_TAG 129 
 int MSG_HEAD_TAG ; 
 int MSG_ORDERED_TAG ; 
 int MSG_SIMPLE_TAG ; 
#define  ORDERED_QUEUE_TAG 128 

__attribute__((used)) static int tcm_loop_sam_attr(struct scsi_cmnd *sc)
{
	if (sc->device->tagged_supported) {
		switch (sc->tag) {
		case HEAD_OF_QUEUE_TAG:
			return MSG_HEAD_TAG;
		case ORDERED_QUEUE_TAG:
			return MSG_ORDERED_TAG;
		default:
			break;
		}
	}

	return MSG_SIMPLE_TAG;
}