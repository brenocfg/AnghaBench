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
struct ev7_pal_zbox_subpacket {int dummy; } ;
struct ev7_pal_rbox_subpacket {int dummy; } ;
struct ev7_pal_processor_subpacket {int dummy; } ;
struct ev7_pal_logout_subpacket {int subpacket_count; } ;
struct ev7_pal_io_subpacket {int dummy; } ;
struct ev7_pal_environmental_subpacket {int dummy; } ;
struct ev7_lf_subpackets {struct ev7_pal_environmental_subpacket** env; struct ev7_pal_io_subpacket* io; struct ev7_pal_zbox_subpacket* zbox; struct ev7_pal_rbox_subpacket* rbox; struct ev7_pal_processor_subpacket* ev7; struct ev7_pal_logout_subpacket* logout; } ;
struct TYPE_3__ {scalar_t__ data_start; } ;
struct TYPE_4__ {TYPE_1__ raw; } ;
struct el_subpacket {scalar_t__ class; scalar_t__ type; TYPE_2__ by_type; scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ EL_CLASS__HEADER ; 
 scalar_t__ EL_CLASS__PAL ; 
 scalar_t__ EL_TYPE__HEADER__LOGOUT_FRAME ; 
#define  EL_TYPE__PAL__ENV__AIRMOVER_FAN 138 
#define  EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE 137 
#define  EL_TYPE__PAL__ENV__HOT_PLUG 136 
#define  EL_TYPE__PAL__ENV__INTRUSION 135 
#define  EL_TYPE__PAL__ENV__LAN 134 
#define  EL_TYPE__PAL__ENV__POWER_SUPPLY 133 
#define  EL_TYPE__PAL__ENV__VOLTAGE 132 
#define  EL_TYPE__PAL__EV7_IO 131 
#define  EL_TYPE__PAL__EV7_PROCESSOR 130 
#define  EL_TYPE__PAL__EV7_RBOX 129 
#define  EL_TYPE__PAL__EV7_ZBOX 128 
 scalar_t__ EL_TYPE__PAL__LOGOUT_FRAME ; 
 int /*<<< orphan*/  err_print_prefix ; 
 size_t ev7_lf_env_index (int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 

struct ev7_lf_subpackets *
ev7_collect_logout_frame_subpackets(struct el_subpacket *el_ptr,
				    struct ev7_lf_subpackets *lf_subpackets)
{
	struct el_subpacket *subpacket;
	int i;

	/*
	 * A Marvel machine check frame is always packaged in an
	 * el_subpacket of class HEADER, type LOGOUT_FRAME.
	 */
	if (el_ptr->class != EL_CLASS__HEADER || 
	    el_ptr->type != EL_TYPE__HEADER__LOGOUT_FRAME)
		return NULL;

	/*
	 * It is a logout frame header. Look at the one subpacket.
	 */
	el_ptr = (struct el_subpacket *)
		((unsigned long)el_ptr + el_ptr->length);

	/*
	 * It has to be class PAL, type LOGOUT_FRAME.
	 */
	if (el_ptr->class != EL_CLASS__PAL ||
	    el_ptr->type != EL_TYPE__PAL__LOGOUT_FRAME)
		return NULL;

	lf_subpackets->logout = (struct ev7_pal_logout_subpacket *)
		el_ptr->by_type.raw.data_start;

	/*
	 * Process the subpackets.
	 */
	subpacket = (struct el_subpacket *)
		((unsigned long)el_ptr + el_ptr->length);
	for (i = 0;
	     subpacket && i < lf_subpackets->logout->subpacket_count;
	     subpacket = (struct el_subpacket *)
		     ((unsigned long)subpacket + subpacket->length), i++) {
		/*
		 * All subpackets should be class PAL.
		 */
		if (subpacket->class != EL_CLASS__PAL) {
			printk("%s**UNEXPECTED SUBPACKET CLASS %d "
			       "IN LOGOUT FRAME (packet %d\n",
			       err_print_prefix, subpacket->class, i);
			return NULL;
		}

		/*
		 * Remember the subpacket.
		 */
		switch(subpacket->type) {
		case EL_TYPE__PAL__EV7_PROCESSOR:
			lf_subpackets->ev7 =
				(struct ev7_pal_processor_subpacket *)
				subpacket->by_type.raw.data_start;
			break;

		case EL_TYPE__PAL__EV7_RBOX:
			lf_subpackets->rbox = (struct ev7_pal_rbox_subpacket *)
				subpacket->by_type.raw.data_start;
			break;

		case EL_TYPE__PAL__EV7_ZBOX:
			lf_subpackets->zbox = (struct ev7_pal_zbox_subpacket *)
				subpacket->by_type.raw.data_start;
			break;

		case EL_TYPE__PAL__EV7_IO:
			lf_subpackets->io = (struct ev7_pal_io_subpacket *)
				subpacket->by_type.raw.data_start;
			break;

		case EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE:
		case EL_TYPE__PAL__ENV__AIRMOVER_FAN:
		case EL_TYPE__PAL__ENV__VOLTAGE:
		case EL_TYPE__PAL__ENV__INTRUSION:
		case EL_TYPE__PAL__ENV__POWER_SUPPLY:
		case EL_TYPE__PAL__ENV__LAN:
		case EL_TYPE__PAL__ENV__HOT_PLUG:
			lf_subpackets->env[ev7_lf_env_index(subpacket->type)] =
 				(struct ev7_pal_environmental_subpacket *)
				subpacket->by_type.raw.data_start;
			break;
				
		default:
			/*
			 * Don't know what kind of frame this is.
			 */
			return NULL;
		}
	}

	return lf_subpackets;
}