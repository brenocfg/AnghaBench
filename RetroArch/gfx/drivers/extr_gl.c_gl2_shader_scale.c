#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* scale; int /*<<< orphan*/  idx; } ;
typedef  TYPE_2__ video_shader_ctx_scale_t ;
struct TYPE_9__ {int /*<<< orphan*/  shader_data; TYPE_1__* shader; } ;
typedef  TYPE_3__ gl_t ;
struct TYPE_10__ {int valid; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* shader_scale ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static bool gl2_shader_scale(gl_t *gl,
      video_shader_ctx_scale_t *scaler)
{
   if (!scaler || !scaler->scale)
      return false;

   scaler->scale->valid = false;

   gl->shader->shader_scale(gl->shader_data,
         scaler->idx, scaler->scale);
   return true;
}