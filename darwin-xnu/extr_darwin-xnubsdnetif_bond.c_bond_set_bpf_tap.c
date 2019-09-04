#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int dummy; } ;
typedef  TYPE_1__* ifbond_ref ;
typedef  int bpf_tap_mode ;
typedef  void* bpf_packet_func ;
struct TYPE_4__ {int /*<<< orphan*/ * ifb_bpf_output; int /*<<< orphan*/ * ifb_bpf_input; } ;

/* Variables and functions */
#define  BPF_TAP_DISABLE 131 
#define  BPF_TAP_INPUT 130 
#define  BPF_TAP_INPUT_OUTPUT 129 
#define  BPF_TAP_OUTPUT 128 
 int ENODEV ; 
 int /*<<< orphan*/  bond_lock () ; 
 int /*<<< orphan*/  bond_unlock () ; 
 scalar_t__ ifbond_flags_if_detaching (TYPE_1__*) ; 
 TYPE_1__* ifnet_softc (struct ifnet*) ; 

__attribute__((used)) static int 
bond_set_bpf_tap(struct ifnet * ifp, bpf_tap_mode mode, bpf_packet_func func)
{
    ifbond_ref	ifb;

    bond_lock();
    ifb = ifnet_softc(ifp);
    if (ifb == NULL || ifbond_flags_if_detaching(ifb)) {
	bond_unlock();
	return (ENODEV);
    }
    switch (mode) {
    case BPF_TAP_DISABLE:
	ifb->ifb_bpf_input = ifb->ifb_bpf_output = NULL;
	break;

    case BPF_TAP_INPUT:
	ifb->ifb_bpf_input = func;
	break;

    case BPF_TAP_OUTPUT:
	ifb->ifb_bpf_output = func;
	break;
        
    case BPF_TAP_INPUT_OUTPUT:
	ifb->ifb_bpf_input = ifb->ifb_bpf_output = func;
	break;
    default:
	break;
    }
    bond_unlock();
    return 0;
}