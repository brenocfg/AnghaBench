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
typedef  int /*<<< orphan*/  u16 ;
struct __gx_tlutobj {int tlut_fmt; int tlut_maddr; int /*<<< orphan*/  tlut_nentries; } ;
typedef  int /*<<< orphan*/  GXTlutObj ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_VIRTUAL_TO_PHYSICAL (void*) ; 
 int _SHIFTL (int,int,int) ; 
 int _SHIFTR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void GX_InitTlutObj(GXTlutObj *obj,void *lut,u8 fmt,u16 entries)
{
	struct __gx_tlutobj *ptr = (struct __gx_tlutobj*)obj;

	memset(obj,0,sizeof(GXTlutObj));

	ptr->tlut_fmt = _SHIFTL(fmt,10,2);
	ptr->tlut_maddr = (ptr->tlut_maddr&~0x00ffffff)|(_SHIFTR(MEM_VIRTUAL_TO_PHYSICAL(lut),5,24));
	ptr->tlut_maddr = (ptr->tlut_maddr&~0xff000000)|(_SHIFTL(0x64,24,8));
	ptr->tlut_nentries = entries;
}