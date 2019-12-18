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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  ETH_P_802_2 132 
#define  ETH_P_802_3 131 
#define  ETH_P_IPX 130 
#define  ETH_P_SNAP 129 
#define  ETH_P_TR_802_2 128 
 int ntohs (int /*<<< orphan*/ ) ; 

const char *ipx_frame_name(__be16 frame)
{
	char* rc = "None";

	switch (ntohs(frame)) {
	case ETH_P_IPX:		rc = "EtherII";	break;
	case ETH_P_802_2:	rc = "802.2";	break;
	case ETH_P_SNAP:	rc = "SNAP";	break;
	case ETH_P_802_3:	rc = "802.3";	break;
	case ETH_P_TR_802_2:	rc = "802.2TR";	break;
	}

	return rc;
}