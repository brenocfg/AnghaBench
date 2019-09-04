#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct knote {int kn_data; TYPE_2__* kn_fp; scalar_t__ kn_vnode_use_ofst; } ;
struct TYPE_4__ {TYPE_1__* f_fglob; } ;
struct TYPE_3__ {scalar_t__ fg_offset; } ;

/* Variables and functions */

__attribute__((used)) static void filt_spec_common(struct knote *kn, int selres)
{
	if (kn->kn_vnode_use_ofst) {
		if (kn->kn_fp->f_fglob->fg_offset >= (uint32_t)selres) {
			kn->kn_data = 0;
		} else {
			kn->kn_data = ((uint32_t)selres) - kn->kn_fp->f_fglob->fg_offset;
		}
	} else {
		kn->kn_data = selres;
	}
}