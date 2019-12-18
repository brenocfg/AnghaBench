#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct el_subpacket {int class; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  EL_CLASS__HEADER 129 
#define  EL_CLASS__TERMINATION 128 
 struct el_subpacket* el_process_header_subpacket (struct el_subpacket*) ; 
 struct el_subpacket* el_process_subpacket_reg (struct el_subpacket*) ; 
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct el_subpacket *
el_process_subpacket(struct el_subpacket *header)
{
	struct el_subpacket *next = NULL;

	switch(header->class) {
	case EL_CLASS__TERMINATION:
		/* Termination packet, there are no more */
		break;
	case EL_CLASS__HEADER: 
		next = el_process_header_subpacket(header);
		break;
	default:
		if (NULL == (next = el_process_subpacket_reg(header))) {
			printk("%s** Unexpected header CLASS %d TYPE %d"
			       " -- aborting.\n",
			       err_print_prefix,
			       header->class, header->type);
		}
		break;
	}

	return next;
}