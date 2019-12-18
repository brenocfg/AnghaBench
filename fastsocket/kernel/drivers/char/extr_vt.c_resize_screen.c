#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vc_data {scalar_t__ vc_mode; TYPE_1__* vc_sw; } ;
struct TYPE_2__ {int (* con_resize ) (struct vc_data*,int,int,int) ;} ;

/* Variables and functions */
 scalar_t__ KD_GRAPHICS ; 
 int stub1 (struct vc_data*,int,int,int) ; 

__attribute__((used)) static inline int resize_screen(struct vc_data *vc, int width, int height,
				int user)
{
	/* Resizes the resolution of the display adapater */
	int err = 0;

	if (vc->vc_mode != KD_GRAPHICS && vc->vc_sw->con_resize)
		err = vc->vc_sw->con_resize(vc, width, height, user);

	return err;
}