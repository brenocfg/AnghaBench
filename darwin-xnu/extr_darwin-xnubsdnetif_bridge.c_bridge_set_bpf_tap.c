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
struct bridge_softc {int sc_flags; int /*<<< orphan*/ * sc_bpf_output; int /*<<< orphan*/ * sc_bpf_input; } ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int bpf_tap_mode ;
typedef  void* bpf_packet_func ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  BPF_TAP_DISABLE 131 
#define  BPF_TAP_INPUT 130 
#define  BPF_TAP_INPUT_OUTPUT 129 
#define  BPF_TAP_OUTPUT 128 
 int /*<<< orphan*/  ENODEV ; 
 int SCF_DETACHING ; 
 int /*<<< orphan*/  bridge_in_bsd_mode (struct bridge_softc*) ; 
 scalar_t__ ifnet_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
bridge_set_bpf_tap(ifnet_t ifp, bpf_tap_mode mode, bpf_packet_func bpf_callback)
{
	struct bridge_softc *sc = (struct bridge_softc *)ifnet_softc(ifp);

	/* TBD locking */
	if (sc == NULL || (sc->sc_flags & SCF_DETACHING)) {
		return (ENODEV);
	}
	ASSERT(bridge_in_bsd_mode(sc));
	switch (mode) {
		case BPF_TAP_DISABLE:
			sc->sc_bpf_input = sc->sc_bpf_output = NULL;
			break;

		case BPF_TAP_INPUT:
			sc->sc_bpf_input = bpf_callback;
			break;

		case BPF_TAP_OUTPUT:
			sc->sc_bpf_output = bpf_callback;
			break;

		case BPF_TAP_INPUT_OUTPUT:
			sc->sc_bpf_input = sc->sc_bpf_output = bpf_callback;
			break;

		default:
			break;
	}

	return (0);
}