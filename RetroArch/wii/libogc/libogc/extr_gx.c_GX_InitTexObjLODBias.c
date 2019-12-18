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
struct __gx_texobj {int tex_filt; } ;
typedef  float f32 ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 int _SHIFTL (int /*<<< orphan*/ ,int,int) ; 

void GX_InitTexObjLODBias(GXTexObj *obj,f32 lodbias)
{
	struct __gx_texobj *ptr = (struct __gx_texobj*)obj;

	if(lodbias<-4.0f) lodbias = -4.0f;
	else if(lodbias==4.0f) lodbias = 3.99f;

	ptr->tex_filt = (ptr->tex_filt&~0x1fe00)|(_SHIFTL(((u32)(32.0f*lodbias)),9,8));
}