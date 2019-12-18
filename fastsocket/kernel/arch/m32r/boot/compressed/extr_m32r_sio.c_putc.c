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
 int* SIO0STS ; 
 char* SIO0TXB ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void putc(char c)
{
	while ((*SIO0STS & 0x1) == 0)
		cpu_relax();
	if (c == '\n') {
		*SIO0TXB = '\r';
		while ((*SIO0STS & 0x1) == 0)
			cpu_relax();
	}
	*SIO0TXB = c;
}