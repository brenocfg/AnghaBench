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
 int call_usermodehelper (char*,char**,char**,int) ; 
 char* v86d_path ; 

__attribute__((used)) static int uvesafb_helper_start(void)
{
	char *envp[] = {
		"HOME=/",
		"PATH=/sbin:/bin",
		NULL,
	};

	char *argv[] = {
		v86d_path,
		NULL,
	};

	return call_usermodehelper(v86d_path, argv, envp, 1);
}