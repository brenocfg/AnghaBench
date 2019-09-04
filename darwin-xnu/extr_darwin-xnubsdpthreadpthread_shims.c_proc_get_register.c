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
typedef  int uint64_t ;
struct proc {int p_lflag; } ;

/* Variables and functions */
 int P_LREGISTER ; 

__attribute__((used)) static uint64_t
proc_get_register(struct proc *p) {
	return (p->p_lflag & P_LREGISTER);
}