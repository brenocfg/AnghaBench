#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int p_flag; } ;

/* Variables and functions */
 int P_CONTROLT ; 

__attribute__((used)) static int
pgsignal_filt(proc_t p, void * arg)
{
	int checkctty = *(int*)arg;

	if ((checkctty == 0) || p->p_flag & P_CONTROLT)
		return(1);
	else 
		return(0);
}