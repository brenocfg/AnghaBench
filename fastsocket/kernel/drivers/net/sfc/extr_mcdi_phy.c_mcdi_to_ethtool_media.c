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

/* Variables and functions */
#define  MC_CMD_MEDIA_BASE_T 133 
#define  MC_CMD_MEDIA_CX4 132 
#define  MC_CMD_MEDIA_KX4 131 
#define  MC_CMD_MEDIA_SFP_PLUS 130 
#define  MC_CMD_MEDIA_XAUI 129 
#define  MC_CMD_MEDIA_XFP 128 
 int PORT_FIBRE ; 
 int PORT_OTHER ; 
 int PORT_TP ; 

__attribute__((used)) static u32 mcdi_to_ethtool_media(u32 media)
{
	switch (media) {
	case MC_CMD_MEDIA_XAUI:
	case MC_CMD_MEDIA_CX4:
	case MC_CMD_MEDIA_KX4:
		return PORT_OTHER;

	case MC_CMD_MEDIA_XFP:
	case MC_CMD_MEDIA_SFP_PLUS:
		return PORT_FIBRE;

	case MC_CMD_MEDIA_BASE_T:
		return PORT_TP;

	default:
		return PORT_OTHER;
	}
}