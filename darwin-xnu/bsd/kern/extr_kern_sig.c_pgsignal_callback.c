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
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int PROC_RETURNED ; 
 int /*<<< orphan*/  psignal (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pgsignal_callback(proc_t p, void * arg)
{
        int  signum = *(int*)arg;

	psignal(p, signum);
	return(PROC_RETURNED);
}