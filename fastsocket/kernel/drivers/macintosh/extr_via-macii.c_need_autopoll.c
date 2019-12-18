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
 int autopoll_devs ; 
 int command_byte ; 

__attribute__((used)) static inline int need_autopoll(void) {
	/* Was the last command Talk Reg 0
	 * and is the target on the autopoll list?
	 */
	if ((command_byte & 0x0F) == 0x0C &&
	    ((1 << ((command_byte & 0xF0) >> 4)) & autopoll_devs))
		return 0;
	return 1;
}