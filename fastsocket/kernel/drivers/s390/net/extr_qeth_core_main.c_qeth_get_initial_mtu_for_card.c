#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; int max_mtu; int /*<<< orphan*/  link_type; } ;
struct qeth_card {TYPE_1__ info; } ;

/* Variables and functions */
#define  QETH_CARD_TYPE_IQD 134 
#define  QETH_CARD_TYPE_OSD 133 
#define  QETH_CARD_TYPE_OSM 132 
#define  QETH_CARD_TYPE_OSX 131 
#define  QETH_CARD_TYPE_UNKNOWN 130 
#define  QETH_LINK_TYPE_HSTR 129 
#define  QETH_LINK_TYPE_LANE_TR 128 

__attribute__((used)) static inline int qeth_get_initial_mtu_for_card(struct qeth_card *card)
{
	switch (card->info.type) {
	case QETH_CARD_TYPE_UNKNOWN:
		return 1500;
	case QETH_CARD_TYPE_IQD:
		return card->info.max_mtu;
	case QETH_CARD_TYPE_OSD:
		switch (card->info.link_type) {
		case QETH_LINK_TYPE_HSTR:
		case QETH_LINK_TYPE_LANE_TR:
			return 2000;
		default:
			return 1492;
		}
	case QETH_CARD_TYPE_OSM:
	case QETH_CARD_TYPE_OSX:
		return 1492;
	default:
		return 1500;
	}
}