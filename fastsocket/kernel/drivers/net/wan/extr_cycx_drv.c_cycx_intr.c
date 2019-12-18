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
struct cycx_hw {scalar_t__ dpmbase; } ;

/* Variables and functions */
 scalar_t__ GEN_CYCX_INTR ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

void cycx_intr(struct cycx_hw *hw)
{
	writew(0, hw->dpmbase + GEN_CYCX_INTR);
}