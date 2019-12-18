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
 int exec_3dsx_actual (char const*,char const**,int) ; 

int exec_3dsx(const char* path, const char** args){
	return exec_3dsx_actual(path, args, true/*appendPath*/);
}