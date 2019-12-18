#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ spi_hal_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  spi_ll_user_start (int /*<<< orphan*/ ) ; 

void spi_hal_user_start(const spi_hal_context_t *hal)
{
    spi_ll_user_start(hal->hw);
}