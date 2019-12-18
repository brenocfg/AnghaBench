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
struct el_subpacket_handler {scalar_t__ class; struct el_subpacket* (* handler ) (struct el_subpacket*) ;struct el_subpacket_handler* next; } ;
struct el_subpacket {scalar_t__ class; } ;

/* Variables and functions */
 struct el_subpacket* stub1 (struct el_subpacket*) ; 
 struct el_subpacket_handler* subpacket_handler_list ; 

__attribute__((used)) static struct el_subpacket *
el_process_subpacket_reg(struct el_subpacket *header)
{
	struct el_subpacket *next = NULL;
	struct el_subpacket_handler *h = subpacket_handler_list;

	for (; h && h->class != header->class; h = h->next);
	if (h) next = h->handler(header);

	return next;
}