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
struct TYPE_4__ {int cardtype; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_PSTN ; 
#define  QTI_LINEJACK 132 
#define  QTI_PHONECARD 131 
#define  QTI_PHONEJACK 130 
#define  QTI_PHONEJACK_LITE 129 
#define  QTI_PHONEJACK_PCI 128 
 int get_play_volume (TYPE_1__*) ; 

__attribute__((used)) static int get_play_volume_linear(IXJ *j)
{
	int volume, newvolume, dspplaymax;

	/* This should normalize the perceived volumes between the different cards caused by differences in the hardware */
	switch (j->cardtype) {
	case QTI_PHONEJACK:
		dspplaymax = 0x380;
		break;
	case QTI_LINEJACK:
		if(j->port == PORT_PSTN) {
			dspplaymax = 0x48;
		} else {
			dspplaymax = 0x100;
		}
		break;
	case QTI_PHONEJACK_LITE:
		dspplaymax = 0x380;
		break;
	case QTI_PHONEJACK_PCI:
		dspplaymax = 0x6C;
		break;
	case QTI_PHONECARD:
		dspplaymax = 100;
		break;
	default:
		return -1;
	}
	volume = get_play_volume(j);
	newvolume = (volume * 100) / dspplaymax;
	if(newvolume > 100)
		newvolume = 100;
	return newvolume;
}