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
 int __execve (char const*,char* const*,char* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 

int kernel_execve(const char *filename, char *const argv[], char *const envp[])
{
	return __execve(filename, argv, envp, current);
}