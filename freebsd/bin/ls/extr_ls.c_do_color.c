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
 scalar_t__ COLORFLAG_ALWAYS ; 
 scalar_t__ COLORFLAG_NEVER ; 
 scalar_t__ colorflag ; 
 int do_color_from_env () ; 

__attribute__((used)) static bool
do_color(void)
{

#ifdef COLORLS
	if (colorflag == COLORFLAG_NEVER)
		return (false);
	else if (colorflag == COLORFLAG_ALWAYS)
		return (true);
#endif
	return (do_color_from_env());
}