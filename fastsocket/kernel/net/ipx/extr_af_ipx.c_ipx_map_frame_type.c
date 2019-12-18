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
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  ETH_P_802_3 ; 
 int /*<<< orphan*/  ETH_P_IPX ; 
 int /*<<< orphan*/  ETH_P_SNAP ; 
#define  IPX_FRAME_8022 131 
#define  IPX_FRAME_8023 130 
#define  IPX_FRAME_ETHERII 129 
#define  IPX_FRAME_SNAP 128 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be16 ipx_map_frame_type(unsigned char type)
{
	__be16 rc = 0;

	switch (type) {
	case IPX_FRAME_ETHERII:	rc = htons(ETH_P_IPX);		break;
	case IPX_FRAME_8022:	rc = htons(ETH_P_802_2);	break;
	case IPX_FRAME_SNAP:	rc = htons(ETH_P_SNAP);		break;
	case IPX_FRAME_8023:	rc = htons(ETH_P_802_3);	break;
	}

	return rc;
}