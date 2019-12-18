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
struct __gx_litobj {void* a2; void* a1; void* a0; } ;
typedef  void* f32 ;
typedef  int /*<<< orphan*/  GXLightObj ;

/* Variables and functions */

void GX_InitLightAttnA(GXLightObj *lit_obj,f32 a0,f32 a1,f32 a2)
{
	struct __gx_litobj *lit = (struct __gx_litobj*)lit_obj;

	lit->a0 = a0;
	lit->a1 = a1;
	lit->a2 = a2;
}