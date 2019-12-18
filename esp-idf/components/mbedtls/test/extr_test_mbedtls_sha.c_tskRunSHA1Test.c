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
typedef  int /*<<< orphan*/  mbedtls_sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_MEMORY_MESSAGE (int /*<<< orphan*/ ,unsigned char*,int,char*) ; 
 int /*<<< orphan*/  done_sem ; 
 int /*<<< orphan*/  mbedtls_sha1_finish_ret (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_starts_ret (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_update_ret (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ one_hundred_as ; 
 int /*<<< orphan*/  sha1_thousand_as ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tskRunSHA1Test(void *pvParameters)
{
    mbedtls_sha1_context sha1_ctx;
    unsigned char sha1[20];

    for (int i = 0; i < 1000; i++) {
        mbedtls_sha1_init(&sha1_ctx);
        TEST_ASSERT_EQUAL(0, mbedtls_sha1_starts_ret(&sha1_ctx));
        for (int j = 0; j < 10; j++) {
            TEST_ASSERT_EQUAL(0, mbedtls_sha1_update_ret(&sha1_ctx, (unsigned char *)one_hundred_as, 100));
        }
        TEST_ASSERT_EQUAL(0, mbedtls_sha1_finish_ret(&sha1_ctx, sha1));
        TEST_ASSERT_EQUAL_MEMORY_MESSAGE(sha1_thousand_as, sha1, 20, "SHA1 calculation");
    }
    xSemaphoreGive(done_sem);
    vTaskDelete(NULL);
}