#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  math_matrix_4x4 ;
struct TYPE_6__ {unsigned int rotation; int /*<<< orphan*/  ubo; } ;
struct TYPE_7__ {TYPE_1__ frame; int /*<<< orphan*/  mvp; int /*<<< orphan*/  mvp_no_rot; } ;
typedef  TYPE_2__ d3d12_video_t ;
struct TYPE_8__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ D3D12_RANGE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D12Map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,void**) ; 
 int /*<<< orphan*/  D3D12Unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 float M_PI ; 
 int /*<<< orphan*/  d3d12_gfx_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  matrix_4x4_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matrix_4x4_rotate_z (int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void d3d12_gfx_set_rotation(void* data, unsigned rotation)
{
   math_matrix_4x4  rot;
   math_matrix_4x4* mvp;
   D3D12_RANGE      read_range = { 0, 0 };
   d3d12_video_t*   d3d12      = (d3d12_video_t*)data;

   if (!d3d12)
      return;

   d3d12_gfx_sync(d3d12);
   d3d12->frame.rotation = rotation;

   matrix_4x4_rotate_z(rot, d3d12->frame.rotation * (M_PI / 2.0f));
   matrix_4x4_multiply(d3d12->mvp, rot, d3d12->mvp_no_rot);

   D3D12Map(d3d12->frame.ubo, 0, &read_range, (void**)&mvp);
   *mvp = d3d12->mvp;
   D3D12Unmap(d3d12->frame.ubo, 0, NULL);
}