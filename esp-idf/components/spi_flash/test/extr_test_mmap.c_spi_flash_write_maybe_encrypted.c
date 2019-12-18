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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_flash_encryption_enabled () ; 
 int /*<<< orphan*/  spi_flash_write (size_t,void const*,size_t) ; 
 int /*<<< orphan*/  spi_flash_write_encrypted (size_t,void const*,size_t) ; 

__attribute__((used)) static esp_err_t spi_flash_write_maybe_encrypted(size_t des_addr, const void *src_addr, size_t size)
{
    if (!esp_flash_encryption_enabled()) {
        return spi_flash_write(des_addr, src_addr, size);
    } else {
        return spi_flash_write_encrypted(des_addr, src_addr, size);
    }
}