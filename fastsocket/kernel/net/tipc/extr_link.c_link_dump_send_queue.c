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
struct link {scalar_t__ first_out; scalar_t__ next_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_print_buf_chain (scalar_t__) ; 
 int /*<<< orphan*/  info (char*) ; 

__attribute__((used)) static void link_dump_send_queue(struct link *l_ptr)
{
	if (l_ptr->next_out) {
		info("\nContents of unsent queue:\n");
		dbg_print_buf_chain(l_ptr->next_out);
	}
	info("\nContents of send queue:\n");
	if (l_ptr->first_out) {
		dbg_print_buf_chain(l_ptr->first_out);
	}
	info("Empty send queue\n");
}