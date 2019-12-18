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
struct c67x00_sie {int /*<<< orphan*/  sie_num; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_IRQ_ROUTING_REG ; 
 int /*<<< orphan*/  SOFEOP_TO_HPI_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void c67x00_ll_hpi_enable_sofeop(struct c67x00_sie *sie)
{
	hpi_set_bits(sie->dev, HPI_IRQ_ROUTING_REG,
		     SOFEOP_TO_HPI_EN(sie->sie_num));
}