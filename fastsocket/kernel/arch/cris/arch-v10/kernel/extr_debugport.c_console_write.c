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
 int /*<<< orphan*/  SIMCOUT (char const*,unsigned int) ; 
 int /*<<< orphan*/  console_write_direct (struct console*,char const*,unsigned int) ; 
 int /*<<< orphan*/  port ; 

__attribute__((used)) static void
console_write(struct console *co, const char *buf, unsigned int len)
{
	if (!port)
		return;

#ifdef CONFIG_SVINTO_SIM
	/* no use to simulate the serial debug output */
	SIMCOUT(buf, len);
	return;
#endif

        console_write_direct(co, buf, len);
}