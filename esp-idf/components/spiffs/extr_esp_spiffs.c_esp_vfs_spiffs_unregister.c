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
typedef  scalar_t__ esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  base_path; } ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_OK ; 
 TYPE_1__** _efs ; 
 scalar_t__ esp_spiffs_by_label (char const*,int*) ; 
 int /*<<< orphan*/  esp_spiffs_free (TYPE_1__**) ; 
 scalar_t__ esp_vfs_unregister (int /*<<< orphan*/ ) ; 

esp_err_t esp_vfs_spiffs_unregister(const char* partition_label)
{
    int index;
    if (esp_spiffs_by_label(partition_label, &index) != ESP_OK) {
        return ESP_ERR_INVALID_STATE;
    }
    esp_err_t err = esp_vfs_unregister(_efs[index]->base_path);
    if (err != ESP_OK) {
        return err;
    }
    esp_spiffs_free(&_efs[index]);
    return ESP_OK;
}