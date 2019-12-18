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

/* Variables and functions */
#define  QETH_CARD_TYPE_IQD 133 
#define  QETH_CARD_TYPE_OSD 132 
#define  QETH_CARD_TYPE_OSM 131 
#define  QETH_CARD_TYPE_OSN 130 
#define  QETH_CARD_TYPE_OSX 129 
#define  QETH_CARD_TYPE_UNKNOWN 128 

__attribute__((used)) static inline int qeth_get_max_mtu_for_card(int cardtype)
{
	switch (cardtype) {

	case QETH_CARD_TYPE_UNKNOWN:
	case QETH_CARD_TYPE_OSD:
	case QETH_CARD_TYPE_OSN:
	case QETH_CARD_TYPE_OSM:
	case QETH_CARD_TYPE_OSX:
		return 61440;
	case QETH_CARD_TYPE_IQD:
		return 57344;
	default:
		return 1500;
	}
}