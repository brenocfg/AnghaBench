#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cardtype; } ;
typedef  TYPE_1__ IXJ ;

/* Variables and functions */
#define  QTI_LINEJACK 132 
#define  QTI_PHONECARD 131 
#define  QTI_PHONEJACK 130 
#define  QTI_PHONEJACK_LITE 129 
#define  QTI_PHONEJACK_PCI 128 
 int get_rec_volume (TYPE_1__*) ; 

__attribute__((used)) static int get_rec_volume_linear(IXJ *j)
{
	int volume, newvolume, dsprecmax;

	switch (j->cardtype) {
	case QTI_PHONEJACK:
		dsprecmax = 0x440;
		break;
	case QTI_LINEJACK:
		dsprecmax = 0x180;
		break;
	case QTI_PHONEJACK_LITE:
		dsprecmax = 0x4C0;
		break;
	case QTI_PHONEJACK_PCI:
		dsprecmax = 0x100;
		break;
	case QTI_PHONECARD:
		dsprecmax = 0x400;
		break;
	default:
		return -1;
	}
	volume = get_rec_volume(j);
	newvolume = (volume * 100) / dsprecmax;
	if(newvolume > 100)
		newvolume = 100;
	return newvolume;
}