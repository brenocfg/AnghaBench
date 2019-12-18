#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct card_direntry {int iconaddr; int bannerfmt; size_t iconfmt; size_t iconspeed; } ;
typedef  size_t s32 ;
struct TYPE_3__ {int banner_fmt; int offset_banner; int offset_banner_tlut; size_t* iconfmt; size_t* iconspeed; int* offset_icon; int* offset_icon_tlut; scalar_t__ icon_speed; scalar_t__ icon_fmt; } ;
typedef  TYPE_1__ card_stat ;

/* Variables and functions */
 int CARD_BANNER_CI ; 
 int CARD_BANNER_MASK ; 
 int CARD_BANNER_RGB ; 
 size_t CARD_ICON_MASK ; 
 size_t CARD_MAXICONS ; 
 size_t CARD_SPEED_MASK ; 

__attribute__((used)) static void __card_updateiconoffsets(struct card_direntry *entry,card_stat *stats)
{
	s32 i;
	u8 bnrfmt,nicons;
	u32 iconaddr,iconbase;

	iconaddr = entry->iconaddr;
	if(iconaddr==-1) {
		stats->banner_fmt = 0;
		stats->icon_fmt = 0;
		stats->icon_speed = 0;
		iconaddr = 0;
	}

	if(entry->bannerfmt&CARD_BANNER_MASK) {
		if(!(entry->bannerfmt&0x10)) {
			bnrfmt = (entry->bannerfmt&CARD_BANNER_MASK);
			if(bnrfmt==CARD_BANNER_CI) {
				stats->banner_fmt = bnrfmt;
				stats->offset_banner = iconaddr;
				stats->offset_banner_tlut = iconaddr+3072;
				iconaddr += (3072+512);
			} else if(bnrfmt==CARD_BANNER_RGB) {
				stats->banner_fmt = bnrfmt;
				stats->offset_banner = iconaddr;
				stats->offset_banner_tlut = -1;
				iconaddr += 6144;
			}
		} else {
			stats->offset_banner = -1;
			stats->offset_banner_tlut = -1;
		}
	}

	nicons = 0;
	for(i=0;i<CARD_MAXICONS;i++) {
		stats->iconfmt[i] = ((entry->iconfmt>>(i<<1))&CARD_ICON_MASK);
		stats->iconspeed[i] = ((entry->iconspeed>>(i<<1))&CARD_SPEED_MASK);
		if(stats->iconspeed[i]==0) stats->iconfmt[i] = 0;
		if(stats->iconfmt[i]) nicons++;
	}

	iconbase = iconaddr;
	for(i=0;i<CARD_MAXICONS;i++) {
		switch(stats->iconfmt[i]) {
			case 1:			//CARD_ICON_CI with shared palette
				stats->offset_icon[i] = iconaddr;
				stats->offset_icon_tlut[i] = iconbase + (nicons*1024);
				iconaddr += 1024;
				break;
			case 2:			//CARD_ICON_RGB
				stats->offset_icon[i] = iconaddr;
				stats->offset_icon_tlut[i] = -1;
				iconaddr += 3072;
				break;
			case 3:			//CARD_ICON_CI with own palette
				stats->offset_icon[i] = iconaddr;
				stats->offset_icon_tlut[i] = iconaddr + 1024;
				iconaddr += 1536;
				break;
			default:		//CARD_ICON_NONE
				stats->offset_icon[i] = -1;
				stats->offset_icon_tlut[i] = -1;
				break;

		}
	}
//	stats->offset_data = iconaddr;
}