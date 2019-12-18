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

/* Variables and functions */
 int /*<<< orphan*/  done_sem ; 
 scalar_t__ mbedtls_sha1_self_test (int) ; 
 scalar_t__ mbedtls_sha256_self_test (int) ; 
 scalar_t__ mbedtls_sha512_self_test (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

void tskRunSHASelftests(void *param)
{
    for (int i = 0; i < 5; i++) {
        if(mbedtls_sha1_self_test(1)) {
            printf("SHA1 self-tests failed.\n");
            while(1) {}
        }

        if(mbedtls_sha256_self_test(1)) {
            printf("SHA256 self-tests failed.\n");
            while(1) {}
        }

        if(mbedtls_sha512_self_test(1)) {
            printf("SHA512 self-tests failed.\n");
            while(1) {}
        }

        if(mbedtls_sha512_self_test(1)) {
            printf("SHA512 self-tests failed.\n");
            while(1) {}
        }
    }
    xSemaphoreGive(done_sem);
    vTaskDelete(NULL);
}