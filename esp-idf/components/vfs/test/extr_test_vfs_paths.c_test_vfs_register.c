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
typedef  int /*<<< orphan*/  esp_vfs_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  dummy_vfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_VFS () ; 
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNITY_TEST_ASSERT_EQUAL_INT (scalar_t__,scalar_t__,int,char*) ; 
 scalar_t__ esp_vfs_register (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_vfs_unregister (char const*) ; 

void test_vfs_register(const char* prefix, bool expect_success, int line)
{
    dummy_vfs_t inst;
    esp_vfs_t desc = DUMMY_VFS();
    esp_err_t err = esp_vfs_register(prefix, &desc, &inst);
    if (expect_success) {
        UNITY_TEST_ASSERT_EQUAL_INT(ESP_OK, err, line, "esp_vfs_register should succeed");
    } else {
        UNITY_TEST_ASSERT_EQUAL_INT(ESP_ERR_INVALID_ARG,
                err, line, "esp_vfs_register should fail");
    }
    if (err == ESP_OK) {
        TEST_ESP_OK( esp_vfs_unregister(prefix) );
    }
}