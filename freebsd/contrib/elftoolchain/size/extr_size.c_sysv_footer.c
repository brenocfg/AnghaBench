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

/* Variables and functions */
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  radix ; 
 int /*<<< orphan*/  tbl_append () ; 
 int /*<<< orphan*/  tbl_flush () ; 
 int /*<<< orphan*/  tbl_print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbl_print_num (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  text_size_total ; 

__attribute__((used)) static void
sysv_footer(void)
{
	tbl_append();
	tbl_print("Total", 0);
	tbl_print_num(text_size_total, radix, 1);
	tbl_flush();
	putchar('\n');
}