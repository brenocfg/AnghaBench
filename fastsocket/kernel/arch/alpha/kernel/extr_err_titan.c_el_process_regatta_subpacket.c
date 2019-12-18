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
struct TYPE_4__ {scalar_t__ data_start; scalar_t__ cpuid; } ;
struct TYPE_3__ {TYPE_2__ regatta_frame; } ;
struct el_subpacket {scalar_t__ class; int type; scalar_t__ length; TYPE_1__ by_type; } ;
struct el_common {int dummy; } ;

/* Variables and functions */
 scalar_t__ EL_CLASS__REGATTA_FAMILY ; 
#define  EL_TYPE__REGATTA__ENVIRONMENTAL_FRAME 132 
#define  EL_TYPE__REGATTA__PROCESSOR_DBL_ERROR_HALT 131 
#define  EL_TYPE__REGATTA__PROCESSOR_ERROR_FRAME 130 
#define  EL_TYPE__REGATTA__SYSTEM_DBL_ERROR_HALT 129 
#define  EL_TYPE__REGATTA__SYSTEM_ERROR_FRAME 128 
 int /*<<< orphan*/  el_annotate_subpacket (struct el_subpacket*) ; 
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,...) ; 
 int privateer_process_logout_frame (struct el_common*,int) ; 

__attribute__((used)) static struct el_subpacket *
el_process_regatta_subpacket(struct el_subpacket *header)
{
	int status;

	if (header->class != EL_CLASS__REGATTA_FAMILY) {
		printk("%s  ** Unexpected header CLASS %d TYPE %d, aborting\n",
		       err_print_prefix,
		       header->class, header->type);
		return NULL;
	}

	switch(header->type) {
	case EL_TYPE__REGATTA__PROCESSOR_ERROR_FRAME:
	case EL_TYPE__REGATTA__SYSTEM_ERROR_FRAME:
	case EL_TYPE__REGATTA__ENVIRONMENTAL_FRAME:
	case EL_TYPE__REGATTA__PROCESSOR_DBL_ERROR_HALT:
	case EL_TYPE__REGATTA__SYSTEM_DBL_ERROR_HALT:
		printk("%s  ** Occurred on CPU %d:\n", 
		       err_print_prefix,
		       (int)header->by_type.regatta_frame.cpuid);
		status = privateer_process_logout_frame((struct el_common *)
			header->by_type.regatta_frame.data_start, 1);
		break;
	default:
		printk("%s  ** REGATTA TYPE %d SUBPACKET\n", 
		       err_print_prefix, header->type);
		el_annotate_subpacket(header);
		break;
	}


	return (struct el_subpacket *)((unsigned long)header + header->length);
}