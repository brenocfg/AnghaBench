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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  card; } ;
typedef  TYPE_1__ esp_slave_context_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  sdmmc_io_read_bytes (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline esp_err_t esp_slave_read_bytes(esp_slave_context_t *context, uint32_t addr, uint8_t *val_o, int len)
{
   return sdmmc_io_read_bytes(context->card, 1, addr&0x3FF, val_o, len);
}