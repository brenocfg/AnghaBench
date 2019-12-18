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
struct m68k_serial {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void m68k_rtsdtr(struct m68k_serial *ss, int set)
{
	if (set) {
		/* set the RTS/CTS line */
	} else {
		/* clear it */
	}
	return;
}