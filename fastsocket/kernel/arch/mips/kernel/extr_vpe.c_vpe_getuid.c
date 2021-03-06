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
struct vpe {int uid; } ;

/* Variables and functions */
 struct vpe* get_vpe (int) ; 

int vpe_getuid(int index)
{
	struct vpe *v;

	if ((v = get_vpe(index)) == NULL)
		return -1;

	return v->uid;
}