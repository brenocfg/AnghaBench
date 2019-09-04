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
struct mbuf {int dummy; } ;
struct label {int dummy; } ;
struct ipq {int /*<<< orphan*/  ipq_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct mbuf*,struct label*,struct ipq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipq_label_associate ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 

void
mac_ipq_label_associate(struct mbuf *fragment, struct ipq *ipq)
{
	struct label *label;

	label = mac_mbuf_to_label(fragment);

	MAC_PERFORM(ipq_label_associate, fragment, label, ipq, ipq->ipq_label);
}