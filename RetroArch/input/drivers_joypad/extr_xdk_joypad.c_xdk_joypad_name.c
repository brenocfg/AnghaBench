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
 char const** XBOX_CONTROLLER_NAMES ; 

__attribute__((used)) static const char *xdk_joypad_name(unsigned pad)
{
   return XBOX_CONTROLLER_NAMES[pad];
}