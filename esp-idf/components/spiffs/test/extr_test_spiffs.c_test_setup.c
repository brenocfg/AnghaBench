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
struct TYPE_3__ {char* base_path; int max_files; int format_if_mount_failed; int /*<<< orphan*/  partition_label; } ;
typedef  TYPE_1__ esp_vfs_spiffs_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_vfs_spiffs_register (TYPE_1__*) ; 
 int /*<<< orphan*/  spiffs_test_partition_label ; 

__attribute__((used)) static void test_setup(void)
{
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = spiffs_test_partition_label,
      .max_files = 5,
      .format_if_mount_failed = true
    };

    TEST_ESP_OK(esp_vfs_spiffs_register(&conf));
}