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
struct consw {int dummy; } ;

/* Variables and functions */
 int MAX_NR_CONSOLES ; 
 struct consw const** con_driver_map ; 

int con_is_bound(const struct consw *csw)
{
	int i, bound = 0;

	for (i = 0; i < MAX_NR_CONSOLES; i++) {
		if (con_driver_map[i] == csw) {
			bound = 1;
			break;
		}
	}

	return bound;
}