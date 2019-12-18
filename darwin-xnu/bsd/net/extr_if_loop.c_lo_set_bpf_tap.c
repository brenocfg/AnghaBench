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
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int bpf_tap_mode ;
typedef  int /*<<< orphan*/ * bpf_packet_func ;
struct TYPE_2__ {int bpf_mode; int /*<<< orphan*/ * bpf_callback; } ;

/* Variables and functions */
#define  BPF_TAP_DISABLE 131 
#define  BPF_TAP_INPUT 130 
#define  BPF_TAP_INPUT_OUTPUT 129 
#define  BPF_TAP_OUTPUT 128 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct ifnet* lo_ifp ; 
 TYPE_1__* lo_statics ; 

__attribute__((used)) static errno_t
lo_set_bpf_tap(struct ifnet *ifp, bpf_tap_mode mode,
    bpf_packet_func bpf_callback)
{
	VERIFY(ifp == lo_ifp);

	lo_statics[0].bpf_mode = mode;

	switch (mode) {
		case BPF_TAP_DISABLE:
		case BPF_TAP_INPUT:
			lo_statics[0].bpf_callback = NULL;
			break;

		case BPF_TAP_OUTPUT:
		case BPF_TAP_INPUT_OUTPUT:
			lo_statics[0].bpf_callback = bpf_callback;
			break;
	}

	return (0);
}