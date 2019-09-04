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
struct label {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_label; } ;
struct bpf_d {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct bpf_d*,struct label*,struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpfdesc_check_receive ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 
 struct label* mac_bpfdesc_label_get (struct bpf_d*) ; 

int
mac_bpfdesc_check_receive(struct bpf_d *bpf_d, struct ifnet *ifp)
{
	struct label *label;
	int error;

	label = mac_bpfdesc_label_get(bpf_d);
	ifnet_lock_shared(ifp);
	MAC_CHECK(bpfdesc_check_receive, bpf_d, label, ifp,
	    ifp->if_label);
	ifnet_lock_done(ifp);

	return (error);
}