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
typedef  int u32 ;
struct __gx_texregion {int tmem_even; int tmem_odd; int ismipmap; int iscached; } ;
typedef  int /*<<< orphan*/  GXTexRegion ;

/* Variables and functions */
#define  GX_TEXCACHE_128K 130 
#define  GX_TEXCACHE_32K 129 
#define  GX_TEXCACHE_512K 128 
 int _SHIFTL (int,int,int) ; 
 int _SHIFTR (int,int,int) ; 

void GX_InitTexCacheRegion(GXTexRegion *region,u8 is32bmipmap,u32 tmem_even,u8 size_even,u32 tmem_odd,u8 size_odd)
{
	u32 sze = 0;
	struct __gx_texregion *ptr = (struct __gx_texregion*)region;

	switch(size_even) {
		case GX_TEXCACHE_32K:
			sze = 3;
			break;
		case GX_TEXCACHE_128K:
			sze = 4;
			break;
		case GX_TEXCACHE_512K:
			sze = 5;
			break;
		default:
			sze = 3;
			break;
	}
	ptr->tmem_even = 0;
	ptr->tmem_even = (ptr->tmem_even&~0x7fff)|(_SHIFTR(tmem_even,5,15));
	ptr->tmem_even = (ptr->tmem_even&~0x38000)|(_SHIFTL(sze,15,3));
	ptr->tmem_even = (ptr->tmem_even&~0x1C0000)|(_SHIFTL(sze,18,3));

	switch(size_odd) {
		case GX_TEXCACHE_32K:
			sze = 3;
			break;
		case GX_TEXCACHE_128K:
			sze = 4;
			break;
		case GX_TEXCACHE_512K:
			sze = 5;
			break;
		default:
			sze = 3;
			break;
	}
	ptr->tmem_odd = 0;
	ptr->tmem_odd = (ptr->tmem_odd&~0x7fff)|(_SHIFTR(tmem_odd,5,15));
	ptr->tmem_odd = (ptr->tmem_odd&~0x38000)|(_SHIFTL(sze,15,3));
	ptr->tmem_odd = (ptr->tmem_odd&~0x1C0000)|(_SHIFTL(sze,18,3));

	ptr->ismipmap = is32bmipmap;
	ptr->iscached = 1;
}