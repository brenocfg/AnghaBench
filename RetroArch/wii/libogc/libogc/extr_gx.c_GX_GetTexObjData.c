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
struct __gx_texobj {int tex_maddr; } ;
typedef  int /*<<< orphan*/  GXTexObj ;

/* Variables and functions */
 scalar_t__ _SHIFTL (int,int,int) ; 

void* GX_GetTexObjData(GXTexObj *obj)
{
	return (void*)(_SHIFTL(((struct __gx_texobj*)obj)->tex_maddr & 0x00ffffff,5,24));
}