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
struct TYPE_2__ {int type; int /*<<< orphan*/  max_mtu; } ;
struct qeth_card {TYPE_1__ info; } ;

/* Variables and functions */
#define  QETH_CARD_TYPE_IQD 133 
#define  QETH_CARD_TYPE_OSD 132 
#define  QETH_CARD_TYPE_OSM 131 
#define  QETH_CARD_TYPE_OSN 130 
#define  QETH_CARD_TYPE_OSX 129 
#define  QETH_CARD_TYPE_UNKNOWN 128 

__attribute__((used)) static inline int qeth_mtu_is_valid(struct qeth_card *card, int mtu)
{
	switch (card->info.type) {
	case QETH_CARD_TYPE_OSD:
	case QETH_CARD_TYPE_OSM:
	case QETH_CARD_TYPE_OSX:
		return ((mtu >= 576) && (mtu <= 61440));
	case QETH_CARD_TYPE_IQD:
		return ((mtu >= 576) &&
			(mtu <= card->info.max_mtu + 4096 - 32));
	case QETH_CARD_TYPE_OSN:
	case QETH_CARD_TYPE_UNKNOWN:
	default:
		return 1;
	}
}