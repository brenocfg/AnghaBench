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
typedef  int u8 ;
typedef  int u16 ;
struct __gx_texobj {int tex_maddr; int tex_size; int tex_fmt; int tex_filt; int tex_flag; } ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 scalar_t__ _SHIFTL (int,int,int) ; 
 void* _SHIFTR (int,int,int) ; 

void GX_GetTexObjAll(GXTexObj* obj, void** image_ptr, u16* width, u16* height,
                     u8* format, u8* wrap_s, u8* wrap_t, u8* mipmap)
{
	struct __gx_texobj *ptr = (struct __gx_texobj*)obj;
	*image_ptr = (void*)(_SHIFTL(ptr->tex_maddr & 0x00ffffff,5,24));
	*width = (ptr->tex_size & 0x3ff) + 1;
	*height = _SHIFTR(ptr->tex_size & 0xffc00, 10, 10) + 1;
	*format = ptr->tex_fmt;
	*wrap_s = ptr->tex_filt & 0x03;
	*wrap_t = _SHIFTR(ptr->tex_filt & 0x0c, 2, 2);
	*mipmap = ptr->tex_flag & 0x01;
}