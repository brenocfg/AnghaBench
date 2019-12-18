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
typedef  void u8 ;
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DCStoreRange (void*,int) ; 
 int /*<<< orphan*/  bba_outsdata (void*,int) ; 
 int /*<<< orphan*/  bba_outsdmadata (void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bba_sync () ; 

__attribute__((used)) static void bba_outsdata_fast(void *val,s32 len)
{
	u32 roundlen;
	s32 missalign;
	u8 *ptr = val;

	if(!val || len<=0) return;

	missalign = -((u32)val)&0x1f;
	if((s32)(len-missalign)<32) {
		bba_outsdata(val,len);
		return;
	}

	if(missalign>0) {
		bba_outsdata(ptr,missalign);
		len -= missalign;
		ptr += missalign;
	}

	roundlen = (len&~0x1f);
	DCStoreRange(ptr,roundlen);
	bba_outsdmadata(ptr,roundlen,NULL);
	bba_sync();

	len -= roundlen;
	ptr += roundlen;
	if(len>0) bba_outsdata(ptr,len);
}