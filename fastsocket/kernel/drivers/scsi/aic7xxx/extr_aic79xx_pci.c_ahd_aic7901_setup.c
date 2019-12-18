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
struct ahd_softc {int /*<<< orphan*/  features; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_AIC7901 ; 
 int /*<<< orphan*/  AHD_AIC7901_FE ; 
 int ahd_aic790X_setup (struct ahd_softc*) ; 

__attribute__((used)) static int
ahd_aic7901_setup(struct ahd_softc *ahd)
{

	ahd->chip = AHD_AIC7901;
	ahd->features = AHD_AIC7901_FE;
	return (ahd_aic790X_setup(ahd));
}