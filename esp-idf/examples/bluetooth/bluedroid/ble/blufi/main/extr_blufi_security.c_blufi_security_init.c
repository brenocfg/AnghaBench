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
struct blufi_security {struct blufi_security* iv; int /*<<< orphan*/  aes; int /*<<< orphan*/  dhm; } ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 struct blufi_security* blufi_sec ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  mbedtls_aes_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_dhm_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct blufi_security*,int,int) ; 

esp_err_t blufi_security_init(void)
{
    blufi_sec = (struct blufi_security *)malloc(sizeof(struct blufi_security));
    if (blufi_sec == NULL) {
        return ESP_FAIL;
    }

    memset(blufi_sec, 0x0, sizeof(struct blufi_security));

    mbedtls_dhm_init(&blufi_sec->dhm);
    mbedtls_aes_init(&blufi_sec->aes);

    memset(blufi_sec->iv, 0x0, 16);
    return 0;
}