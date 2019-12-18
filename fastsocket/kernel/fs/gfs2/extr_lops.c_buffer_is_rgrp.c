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
struct gfs2_bufdata {TYPE_2__* bd_gl; } ;
struct TYPE_3__ {scalar_t__ ln_type; } ;
struct TYPE_4__ {TYPE_1__ gl_name; } ;

/* Variables and functions */
 scalar_t__ LM_TYPE_RGRP ; 

__attribute__((used)) static bool buffer_is_rgrp(const struct gfs2_bufdata *bd)
{
	return bd->bd_gl->gl_name.ln_type == LM_TYPE_RGRP;
}