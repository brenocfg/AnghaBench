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

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 int /*<<< orphan*/  B ; 
 int /*<<< orphan*/  C ; 
 int /*<<< orphan*/  D ; 
 int /*<<< orphan*/  I1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X1 ; 
 int /*<<< orphan*/  X2 ; 
 int /*<<< orphan*/  Y1 ; 
 int /*<<< orphan*/  Y2 ; 
 int /*<<< orphan*/  Z1 ; 
 int /*<<< orphan*/  Z2 ; 
 int /*<<< orphan*/  init_shared_classes () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  lockdep_reset () ; 

__attribute__((used)) static void reset_locks(void)
{
	local_irq_disable();
	I1(A); I1(B); I1(C); I1(D);
	I1(X1); I1(X2); I1(Y1); I1(Y2); I1(Z1); I1(Z2);
	lockdep_reset();
	I2(A); I2(B); I2(C); I2(D);
	init_shared_classes();
	local_irq_enable();
}