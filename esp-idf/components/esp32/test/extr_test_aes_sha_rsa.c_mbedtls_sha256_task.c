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
typedef  int /*<<< orphan*/  xSemaphoreHandle ;
typedef  int /*<<< orphan*/  output ;
typedef  int /*<<< orphan*/  mbedtls_sha256_context ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_MEMORY_MESSAGE (unsigned char*,unsigned char*,int,char*) ; 
 int exit_flag ; 
 int /*<<< orphan*/  mbedtls_sha256_finish_ret (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_starts_ret (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_sha256_update_ret (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mbedtls_sha256_task(void *pvParameters)
{
    xSemaphoreHandle *sema = (xSemaphoreHandle *) pvParameters;
    ESP_LOGI(TAG, "mbedtls_sha256_task is started");
    const char *input = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_abcdefghijklmnopqrstuvwxyz~DEL0123456789Space!#$%&()*+,-.0123456789:;<=>?";
    mbedtls_sha256_context sha256_ctx;
    unsigned char output[32];
    unsigned char output_origin[32];

    mbedtls_sha256_init(&sha256_ctx);
    memset(output, 0, sizeof(output));
    mbedtls_sha256_starts_ret(&sha256_ctx, false);
    for (int i = 0; i < 3; ++i) {
        mbedtls_sha256_update_ret(&sha256_ctx, (unsigned char *)input, 100);
    }
    mbedtls_sha256_finish_ret(&sha256_ctx, output);
    memcpy(output_origin, output, sizeof(output));

    while (exit_flag == false) {
        mbedtls_sha256_init(&sha256_ctx);
        memset(output, 0, sizeof(output));
        mbedtls_sha256_starts_ret(&sha256_ctx, false);
        for (int i = 0; i < 3; ++i) {
            mbedtls_sha256_update_ret(&sha256_ctx, (unsigned char *)input, 100);
        }
        mbedtls_sha256_finish_ret(&sha256_ctx, output);

        TEST_ASSERT_EQUAL_MEMORY_MESSAGE(output, output_origin, sizeof(output), "MBEDTLS SHA256 must match");
    }
    xSemaphoreGive(*sema);
    vTaskDelete(NULL);
}