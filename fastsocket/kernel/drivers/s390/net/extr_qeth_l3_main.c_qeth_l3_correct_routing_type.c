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
struct TYPE_2__ {scalar_t__ type; } ;
struct qeth_card {TYPE_1__ info; } ;
typedef  enum qeth_routing_types { ____Placeholder_qeth_routing_types } qeth_routing_types ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;

/* Variables and functions */
 int /*<<< orphan*/  IPA_OSA_MC_ROUTER ; 
#define  MULTICAST_ROUTER 133 
#define  NO_ROUTER 132 
#define  PRIMARY_CONNECTOR 131 
#define  PRIMARY_ROUTER 130 
 scalar_t__ QETH_CARD_TYPE_IQD ; 
#define  SECONDARY_CONNECTOR 129 
#define  SECONDARY_ROUTER 128 
 int /*<<< orphan*/  qeth_is_ipafunc_supported (struct qeth_card*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qeth_l3_correct_routing_type(struct qeth_card *card,
		enum qeth_routing_types *type, enum qeth_prot_versions prot)
{
	if (card->info.type == QETH_CARD_TYPE_IQD) {
		switch (*type) {
		case NO_ROUTER:
		case PRIMARY_CONNECTOR:
		case SECONDARY_CONNECTOR:
		case MULTICAST_ROUTER:
			return;
		default:
			goto out_inval;
		}
	} else {
		switch (*type) {
		case NO_ROUTER:
		case PRIMARY_ROUTER:
		case SECONDARY_ROUTER:
			return;
		case MULTICAST_ROUTER:
			if (qeth_is_ipafunc_supported(card, prot,
						      IPA_OSA_MC_ROUTER))
				return;
		default:
			goto out_inval;
		}
	}
out_inval:
	*type = NO_ROUTER;
}