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
struct vpe {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int MAX_VPES ; 
 int /*<<< orphan*/  VPE_STATE_INUSE ; 
 struct vpe* get_vpe (int) ; 

vpe_handle vpe_alloc(void)
{
	int i;
	struct vpe *v;

	/* find a vpe */
	for (i = 1; i < MAX_VPES; i++) {
		if ((v = get_vpe(i)) != NULL) {
			v->state = VPE_STATE_INUSE;
			return v;
		}
	}
	return NULL;
}