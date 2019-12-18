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
#define  QETH_CARD_TYPE_IQD 128 

__attribute__((used)) static inline int qeth_get_mtu_out_of_mpc(int cardtype)
{
	switch (cardtype) {
	case QETH_CARD_TYPE_IQD:
		return 1;
	default:
		return 0;
	}
}