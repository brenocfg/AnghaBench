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
struct ahc_softc {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_HVD ; 
 int ahc_aha394XU_setup (struct ahc_softc*) ; 

__attribute__((used)) static int
ahc_aha394XUh_setup(struct ahc_softc *ahc)
{
	int error = ahc_aha394XU_setup(ahc);

	ahc->features |= AHC_HVD;

	return error;
}