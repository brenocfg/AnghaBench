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
struct __gx_litobj {void* pz; void* py; void* px; } ;
typedef  void* f32 ;
typedef  int /*<<< orphan*/  GXLightObj ;

/* Variables and functions */

void GX_InitLightPos(GXLightObj *lit_obj,f32 x,f32 y,f32 z)
{
	struct __gx_litobj *lit = (struct __gx_litobj*)lit_obj;

	lit->px = x;
	lit->py = y;
	lit->pz = z;
}