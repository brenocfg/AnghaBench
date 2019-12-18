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
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9 ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_set_vertex_shader_constantf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float const*,int) ; 

void d3d9_set_mvp(void *data, const void *mat_data)
{
   LPDIRECT3DDEVICE9 dev = (LPDIRECT3DDEVICE9)data;
   d3d9_set_vertex_shader_constantf(dev, 0, (const float*)mat_data, 4);
}