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
typedef  int /*<<< orphan*/  u8 ;
struct __gx_texobj {int tex_filt; } ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 int _SHIFTL (int /*<<< orphan*/ ,int,int) ; 

void GX_InitTexObjBiasClamp(GXTexObj *obj,u8 biasclamp)
{
	struct __gx_texobj *ptr = (struct __gx_texobj*)obj;
	ptr->tex_filt = (ptr->tex_filt&~0x200000)|(_SHIFTL(biasclamp,21,1));
}