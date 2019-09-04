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
struct bridge_softc {int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCF_BSD_MODE ; 

__attribute__((used)) static inline void
bridge_set_bsd_mode(struct bridge_softc * sc)
{
	sc->sc_flags |= SCF_BSD_MODE;
}