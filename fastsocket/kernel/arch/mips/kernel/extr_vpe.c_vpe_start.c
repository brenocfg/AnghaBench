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
typedef  struct vpe* vpe_handle ;
struct vpe {unsigned long __start; } ;

/* Variables and functions */
 int vpe_run (struct vpe*) ; 

int vpe_start(vpe_handle vpe, unsigned long start)
{
	struct vpe *v = vpe;

	v->__start = start;
	return vpe_run(v);
}