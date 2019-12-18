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
 int S_IREAD ; 
 int S_IWRITE ; 
 scalar_t__ chmod (char const*,int) ; 

__attribute__((used)) static int Devices_SetReadOnly(const char *filename, int readonly)
{
	return chmod(filename, readonly ? S_IREAD : (S_IREAD | S_IWRITE)) == 0;
}