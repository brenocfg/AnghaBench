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
struct __gx_texregion {int tmem_even; int tmem_odd; int size_even; int size_odd; scalar_t__ iscached; scalar_t__ ismipmap; } ;
typedef  int /*<<< orphan*/  GXTexRegion ;

/* Variables and functions */
 int _SHIFTR (int /*<<< orphan*/ ,int,int) ; 

void GX_InitTexPreloadRegion(GXTexRegion *region,u32 tmem_even,u32 size_even,u32 tmem_odd,u32 size_odd)
{
	struct __gx_texregion *ptr = (struct __gx_texregion*)region;

	ptr->tmem_even = 0;
	ptr->tmem_even = (ptr->tmem_even&~0x7FFF)|(_SHIFTR(tmem_even,5,15));
	ptr->tmem_even = (ptr->tmem_even&~0x200000)|0x200000;

	ptr->tmem_odd = 0;
	ptr->tmem_odd = (ptr->tmem_odd&~0x7FFF)|(_SHIFTR(tmem_odd,5,15));

	ptr->size_even = _SHIFTR(size_even,5,16);
	ptr->size_odd = _SHIFTR(size_odd,5,16);

	ptr->ismipmap = 0;
	ptr->iscached = 0;
}