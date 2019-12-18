#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  master; } ;
struct uwire_spi {TYPE_1__ bitbang; int /*<<< orphan*/  ck; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWIRE_SR3 ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_master_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwire_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uwire_off(struct uwire_spi *uwire)
{
	uwire_write_reg(UWIRE_SR3, 0);
	clk_disable(uwire->ck);
	clk_put(uwire->ck);
	spi_master_put(uwire->bitbang.master);
}