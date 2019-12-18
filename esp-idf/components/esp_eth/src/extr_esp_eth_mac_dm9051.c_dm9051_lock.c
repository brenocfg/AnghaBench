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
struct TYPE_3__ {int /*<<< orphan*/  spi_lock; } ;
typedef  TYPE_1__ emac_dm9051_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM9051_SPI_LOCK_TIMEOUT_MS ; 
 scalar_t__ pdTRUE ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool dm9051_lock(emac_dm9051_t *emac)
{
    return xSemaphoreTake(emac->spi_lock, DM9051_SPI_LOCK_TIMEOUT_MS) == pdTRUE;
}