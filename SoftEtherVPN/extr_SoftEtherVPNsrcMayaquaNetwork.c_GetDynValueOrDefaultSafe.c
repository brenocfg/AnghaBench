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
typedef  int UINT64 ;

/* Variables and functions */
 int GetDynValueOrDefault (char*,int,int,int) ; 

UINT64 GetDynValueOrDefaultSafe(char *name, UINT64 default_value)
{
	return GetDynValueOrDefault(name, default_value, default_value / (UINT64)5, default_value * (UINT64)50);
}