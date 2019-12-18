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
typedef  int /*<<< orphan*/  u64 ;
struct amo {int /*<<< orphan*/  variable; } ;

/* Variables and functions */
 int /*<<< orphan*/  FETCHOP_CLEAR ; 
 int /*<<< orphan*/  FETCHOP_LOAD_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TO_AMO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64
xpc_receive_IRQ_amo_sn2(struct amo *amo)
{
	return FETCHOP_LOAD_OP(TO_AMO((u64)&amo->variable), FETCHOP_CLEAR);
}