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
typedef  int /*<<< orphan*/  kpc_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  SREG_OPMAT0 ; 
 int /*<<< orphan*/  SREG_OPMAT1 ; 
 int /*<<< orphan*/  SREG_OPMSK0 ; 
 int /*<<< orphan*/  SREG_OPMSK1 ; 
 int /*<<< orphan*/  SREG_PMCR2 ; 
 int /*<<< orphan*/  SREG_PMCR3 ; 
 int /*<<< orphan*/  SREG_PMCR4 ; 
 int /*<<< orphan*/  SREG_PMMMAP ; 
 int /*<<< orphan*/  SREG_PMTRHLD2 ; 
 int /*<<< orphan*/  SREG_PMTRHLD4 ; 
 int /*<<< orphan*/  SREG_PMTRHLD6 ; 
 int /*<<< orphan*/  SREG_READ (int /*<<< orphan*/ ) ; 

int
kpc_get_rawpmu_config(kpc_config_t *configv)
{
	configv[0] = SREG_READ(SREG_PMCR2);
	configv[1] = SREG_READ(SREG_PMCR3);
	configv[2] = SREG_READ(SREG_PMCR4);
	configv[3] = SREG_READ(SREG_OPMAT0);
	configv[4] = SREG_READ(SREG_OPMAT1);
	configv[5] = SREG_READ(SREG_OPMSK0);
	configv[6] = SREG_READ(SREG_OPMSK1);
#if RAWPMU_CONFIG_COUNT > 7
	configv[7] = SREG_READ(SREG_PMMMAP);
	configv[8] = SREG_READ(SREG_PMTRHLD2);
	configv[9] = SREG_READ(SREG_PMTRHLD4);
	configv[10] = SREG_READ(SREG_PMTRHLD6);
#endif
	return 0;
}