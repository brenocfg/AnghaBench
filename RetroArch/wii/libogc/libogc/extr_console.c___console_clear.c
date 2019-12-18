#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int con_xres; int con_yres; scalar_t__ saved_col; scalar_t__ saved_row; scalar_t__ cursor_col; scalar_t__ cursor_row; int /*<<< orphan*/  background; scalar_t__ destbuffer; } ;
typedef  TYPE_1__ console_data_s ;

/* Variables and functions */
 TYPE_1__* curr_con ; 

__attribute__((used)) static void __console_clear(void)
{
	console_data_s *con;
	unsigned int c;
	unsigned int *p;

	if( !(con = curr_con) ) return;

	c = (con->con_xres*con->con_yres)/2;
	p = (unsigned int*)con->destbuffer;

	while(c--)
		*p++ = con->background;

	con->cursor_row = 0;
	con->cursor_col = 0;
	con->saved_row = 0;
	con->saved_col = 0;
}