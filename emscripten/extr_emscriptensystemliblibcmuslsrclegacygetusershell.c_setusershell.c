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
 scalar_t__ defshells ; 
 scalar_t__ f ; 
 scalar_t__ fmemopen (void*,int,char*) ; 
 scalar_t__ fopen (char*,char*) ; 

void setusershell(void)
{
	if (!f) f = fopen("/etc/shells", "rbe");
	if (!f) f = fmemopen((void *)defshells, sizeof defshells - 1, "rb");
}