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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_tee ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int,int,size_t,unsigned int) ; 

ssize_t tee(int src, int dest, size_t len, unsigned flags)
{
	return syscall(SYS_tee, src, dest, len, flags);
}