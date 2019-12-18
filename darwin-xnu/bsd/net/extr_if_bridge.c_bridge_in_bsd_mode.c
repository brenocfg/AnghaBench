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
struct bridge_softc {int sc_flags; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int SCF_BSD_MODE ; 

__attribute__((used)) static inline boolean_t
bridge_in_bsd_mode(const struct bridge_softc * sc)
{
	return ((sc->sc_flags & SCF_BSD_MODE) != 0);
}