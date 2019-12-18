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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_ca_en50221 {scalar_t__ data; } ;
struct budget_ci {int /*<<< orphan*/  budget; } ;

/* Variables and functions */
 int DEBIADDR_ATTR ; 
 int /*<<< orphan*/  DEBICICAM ; 
 int EINVAL ; 
 int ttpci_budget_debiwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ciintf_write_attribute_mem(struct dvb_ca_en50221 *ca, int slot, int address, u8 value)
{
	struct budget_ci *budget_ci = (struct budget_ci *) ca->data;

	if (slot != 0)
		return -EINVAL;

	return ttpci_budget_debiwrite(&budget_ci->budget, DEBICICAM,
				      DEBIADDR_ATTR | (address & 0xfff), 1, value, 1, 0);
}