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
typedef  int u32 ;
struct de_private {int media_advertise; } ;

/* Variables and functions */
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_AUI ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_BNC ; 
#define  DE_MEDIA_AUI 132 
#define  DE_MEDIA_BNC 131 
#define  DE_MEDIA_TP 130 
#define  DE_MEDIA_TP_AUTO 129 
#define  DE_MEDIA_TP_FD 128 

__attribute__((used)) static unsigned int de_ok_to_advertise (struct de_private *de, u32 new_media)
{
	switch (new_media) {
	case DE_MEDIA_TP_AUTO:
		if (!(de->media_advertise & ADVERTISED_Autoneg))
			return 0;
		if (!(de->media_advertise & (ADVERTISED_10baseT_Half | ADVERTISED_10baseT_Full)))
			return 0;
		break;
	case DE_MEDIA_BNC:
		if (!(de->media_advertise & ADVERTISED_BNC))
			return 0;
		break;
	case DE_MEDIA_AUI:
		if (!(de->media_advertise & ADVERTISED_AUI))
			return 0;
		break;
	case DE_MEDIA_TP:
		if (!(de->media_advertise & ADVERTISED_10baseT_Half))
			return 0;
		break;
	case DE_MEDIA_TP_FD:
		if (!(de->media_advertise & ADVERTISED_10baseT_Full))
			return 0;
		break;
	}

	return 1;
}