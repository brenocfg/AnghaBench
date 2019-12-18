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
 int /*<<< orphan*/  SREG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kpc_set_rawpmu_config(kpc_config_t *configv)
{
	SREG_WRITE(SREG_PMCR2, configv[0]);
	SREG_WRITE(SREG_PMCR3, configv[1]);
	SREG_WRITE(SREG_PMCR4, configv[2]);
	SREG_WRITE(SREG_OPMAT0, configv[3]);
	SREG_WRITE(SREG_OPMAT1, configv[4]);
	SREG_WRITE(SREG_OPMSK0, configv[5]);
	SREG_WRITE(SREG_OPMSK1, configv[6]);
#if RAWPMU_CONFIG_COUNT > 7
	SREG_WRITE(SREG_PMMMAP, configv[7]);
	SREG_WRITE(SREG_PMTRHLD2, configv[8]);
	SREG_WRITE(SREG_PMTRHLD4, configv[9]);
	SREG_WRITE(SREG_PMTRHLD6, configv[10]);
#endif
	return 0;
}