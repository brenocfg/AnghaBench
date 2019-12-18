#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  math_matrix_4x4 ;
struct TYPE_7__ {int /*<<< orphan*/  ubo; } ;
struct TYPE_6__ {int /*<<< orphan*/  mvp; } ;
struct TYPE_8__ {TYPE_2__ frame; int /*<<< orphan*/  context; int /*<<< orphan*/  mvp; TYPE_1__ ubo_values; } ;
typedef  TYPE_3__ d3d11_video_t ;
struct TYPE_9__ {scalar_t__ pData; } ;
typedef  TYPE_4__ D3D11_MAPPED_SUBRESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11MapBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  D3D11UnmapBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D3D11_MAP_WRITE_DISCARD ; 
 float M_PI ; 
 int /*<<< orphan*/  matrix_4x4_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_4x4_rotate_z (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void d3d11_gfx_set_rotation(void* data, unsigned rotation)
{
   math_matrix_4x4 rot;
   D3D11_MAPPED_SUBRESOURCE mapped_ubo;
   d3d11_video_t*  d3d11 = (d3d11_video_t*)data;

   if (!d3d11)
      return;

   matrix_4x4_rotate_z(rot, rotation * (M_PI / 2.0f));
   matrix_4x4_multiply(d3d11->mvp, rot, d3d11->ubo_values.mvp);

   D3D11MapBuffer(d3d11->context, d3d11->frame.ubo, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_ubo);
   *(math_matrix_4x4*)mapped_ubo.pData = d3d11->mvp;
   D3D11UnmapBuffer(d3d11->context, d3d11->frame.ubo, 0);
}