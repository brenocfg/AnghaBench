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
 int /*<<< orphan*/  spi_flash_read (size_t,void*,size_t) ; 
 int /*<<< orphan*/  spi_flash_read_encrypted (size_t,void*,size_t) ; 

__attribute__((used)) static esp_err_t spi_flash_read_maybe_encrypted(size_t src_addr, void *des_addr, size_t size)
{
    if (!esp_flash_encryption_enabled()) {
        return spi_flash_read(src_addr, des_addr, size);
    } else {
        return spi_flash_read_encrypted(src_addr, des_addr, size);
    }
}