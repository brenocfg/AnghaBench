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
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  int /*<<< orphan*/  idtype_t ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_waitid ; 
 int syscall_cp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int waitid(idtype_t type, id_t id, siginfo_t *info, int options)
{
	return syscall_cp(SYS_waitid, type, id, info, options, 0);
}