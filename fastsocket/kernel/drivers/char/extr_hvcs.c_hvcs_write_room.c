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
struct tty_struct {struct hvcs_struct* driver_data; } ;
struct hvcs_struct {scalar_t__ open_count; int chars_in_buffer; } ;

/* Variables and functions */
 int HVCS_BUFF_LEN ; 

__attribute__((used)) static int hvcs_write_room(struct tty_struct *tty)
{
	struct hvcs_struct *hvcsd = tty->driver_data;

	if (!hvcsd || hvcsd->open_count <= 0)
		return 0;

	return HVCS_BUFF_LEN - hvcsd->chars_in_buffer;
}