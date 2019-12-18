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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RDSR ; 
 int /*<<< orphan*/  spi_flash_common_read_qe_sr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

esp_err_t spi_flash_common_read_status_8b_rdsr(esp_flash_t* chip, uint32_t* out_sr)
{
    return spi_flash_common_read_qe_sr(chip, CMD_RDSR, 8, out_sr);
}