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
 int /*<<< orphan*/  ia64_sn_console_getc (int*) ; 

__attribute__((used)) static int snt_poll_getc(void)
{
	int ch;

	ia64_sn_console_getc(&ch);
	return ch;
}