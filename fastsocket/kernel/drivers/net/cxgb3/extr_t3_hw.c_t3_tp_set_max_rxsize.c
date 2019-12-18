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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_PARA_REG7 ; 
 int V_PMMAXXFERLEN0 (unsigned int) ; 
 int V_PMMAXXFERLEN1 (unsigned int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void t3_tp_set_max_rxsize(struct adapter *adap, unsigned int size)
{
	t3_write_reg(adap, A_TP_PARA_REG7,
		     V_PMMAXXFERLEN0(size) | V_PMMAXXFERLEN1(size));
}