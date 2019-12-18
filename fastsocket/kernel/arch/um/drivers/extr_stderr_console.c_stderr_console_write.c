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
struct console {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_write (int,char const*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stderr_console_write(struct console *console, const char *string,
				 unsigned len)
{
	generic_write(2 /* stderr */, string, len, NULL);
}