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
typedef  int /*<<< orphan*/  mbedtls_sha256_context ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_MEMORY_MESSAGE (int /*<<< orphan*/ ,unsigned char*,int,char*) ; 
 int /*<<< orphan*/  done_sem ; 
 int /*<<< orphan*/  mbedtls_sha256_finish_ret (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_starts_ret (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_sha256_update_ret (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ one_hundred_bs ; 
 int /*<<< orphan*/  sha256_thousand_bs ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tskRunSHA256Test(void *pvParameters)
{
    mbedtls_sha256_context sha256_ctx;
    unsigned char sha256[32];

    for (int i = 0; i < 1000; i++) {
        mbedtls_sha256_init(&sha256_ctx);
        TEST_ASSERT_EQUAL(0, mbedtls_sha256_starts_ret(&sha256_ctx, false));
        for (int j = 0; j < 10; j++) {
            TEST_ASSERT_EQUAL(0, mbedtls_sha256_update_ret(&sha256_ctx, (unsigned char *)one_hundred_bs, 100));
        }
        TEST_ASSERT_EQUAL(0, mbedtls_sha256_finish_ret(&sha256_ctx, sha256));

        TEST_ASSERT_EQUAL_MEMORY_MESSAGE(sha256_thousand_bs, sha256, 32, "SHA256 calculation");
    }
    xSemaphoreGive(done_sem);
    vTaskDelete(NULL);
}