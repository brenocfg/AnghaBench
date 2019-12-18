#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* shader; } ;
typedef  TYPE_3__ glsl_shader_data_t ;
struct TYPE_5__ {TYPE_1__* pass; } ;
struct TYPE_4__ {int mipmap; } ;

/* Variables and functions */

__attribute__((used)) static bool gl_glsl_mipmap_input(void *data, unsigned idx)
{
   glsl_shader_data_t *glsl = (glsl_shader_data_t*)data;
   if (glsl && idx)
      return glsl->shader->pass[idx - 1].mipmap;
   return false;
}