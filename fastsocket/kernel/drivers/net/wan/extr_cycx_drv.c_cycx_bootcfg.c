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
 scalar_t__ CONF_OFFSET ; 
 int /*<<< orphan*/  FIXED_BUFFERS ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cycx_bootcfg(struct cycx_hw *hw)
{
	/* use fixed buffers */
	writeb(FIXED_BUFFERS, hw->dpmbase + CONF_OFFSET);
}