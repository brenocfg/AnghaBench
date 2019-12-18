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
struct pl022 {int /*<<< orphan*/  virtbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_ALL_INTERRUPTS ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_CPSR ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_CR0 ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_CR1 ; 
 int /*<<< orphan*/  DEFAULT_SSP_REG_DMACR ; 
 int /*<<< orphan*/  DISABLE_ALL_INTERRUPTS ; 
 int /*<<< orphan*/  SSP_CPSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_CR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_CR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_DMACR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_ICR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_IMSC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void load_ssp_default_config(struct pl022 *pl022)
{
	writew(DEFAULT_SSP_REG_CR0, SSP_CR0(pl022->virtbase));
	writew(DEFAULT_SSP_REG_CR1, SSP_CR1(pl022->virtbase));
	writew(DEFAULT_SSP_REG_DMACR, SSP_DMACR(pl022->virtbase));
	writew(DEFAULT_SSP_REG_CPSR, SSP_CPSR(pl022->virtbase));
	writew(DISABLE_ALL_INTERRUPTS, SSP_IMSC(pl022->virtbase));
	writew(CLEAR_ALL_INTERRUPTS, SSP_ICR(pl022->virtbase));
}