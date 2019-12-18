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
 char const* na ; 
 char const** versionNames ; 

__attribute__((used)) static const char *
mpc_get_version_string(float profile) // profile is 0...15, where 7...13 is used
{
	return profile >= sizeof versionNames / sizeof *versionNames ? na : versionNames[(int)profile];
}