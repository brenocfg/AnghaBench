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
typedef  int u32 ;
struct __gx_texobj {int tex_lod; } ;
typedef  float f32 ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */

void GX_InitTexObjMinLOD(GXTexObj *obj,f32 minlod)
{
	struct __gx_texobj *ptr = (struct __gx_texobj*)obj;

	if(minlod<0.0f) minlod = 0.0f;
	else if(minlod>10.0f) minlod = 10.0f;

	ptr->tex_lod = (ptr->tex_lod&~0xff)|(((u32)(16.0f*minlod))&0xff);
}