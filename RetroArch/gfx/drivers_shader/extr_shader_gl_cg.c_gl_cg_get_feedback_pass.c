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
struct TYPE_4__ {TYPE_1__* shader; } ;
typedef  TYPE_2__ cg_shader_data_t ;
struct TYPE_3__ {scalar_t__ feedback_pass; } ;

/* Variables and functions */

__attribute__((used)) static bool gl_cg_get_feedback_pass(void *data, unsigned *pass)
{
   cg_shader_data_t *cg = (cg_shader_data_t*)data;
   if (!cg || cg->shader->feedback_pass < 0)
      return false;

   *pass = cg->shader->feedback_pass;
   return true;
}