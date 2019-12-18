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
typedef  int /*<<< orphan*/  u32 ;
struct __gx_texobj {int tex_lod; } ;
typedef  float f32 ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 int _SHIFTL (int /*<<< orphan*/ ,int,int) ; 

void GX_InitTexObjMaxLOD(GXTexObj *obj,f32 maxlod)
{
	struct __gx_texobj *ptr = (struct __gx_texobj*)obj;

	if(maxlod<0.0f) maxlod = 0.0f;
	else if(maxlod>10.0f) maxlod = 10.0f;

	ptr->tex_lod = (ptr->tex_lod&~0xff00)|(_SHIFTL(((u32)(16.0f*maxlod)),8,8));
}