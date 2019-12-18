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
struct av7110 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBINOSWAP ; 
 int /*<<< orphan*/  IRQ_RX ; 
 int /*<<< orphan*/  iwdebi (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ARM_ClearMailBox(struct av7110 *av7110)
{
	iwdebi(av7110, DEBINOSWAP, IRQ_RX, 0, 2);
}