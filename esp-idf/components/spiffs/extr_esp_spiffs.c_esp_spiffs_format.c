#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ s32_t ;
struct TYPE_5__ {int format_if_mount_failed; char const* partition_label; int max_files; } ;
typedef  TYPE_1__ esp_vfs_spiffs_conf_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_6__ {int /*<<< orphan*/  fs; int /*<<< orphan*/  cache_sz; int /*<<< orphan*/  cache; int /*<<< orphan*/  fds_sz; int /*<<< orphan*/  fds; int /*<<< orphan*/  work; int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ SPIFFS_OK ; 
 int /*<<< orphan*/  SPIFFS_clearerr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ SPIFFS_format (int /*<<< orphan*/ ) ; 
 scalar_t__ SPIFFS_mount (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SPIFFS_mounted (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_unmount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_3__** _efs ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ esp_spiffs_by_label (char const*,int*) ; 
 int /*<<< orphan*/  esp_spiffs_free (TYPE_3__**) ; 
 scalar_t__ esp_spiffs_init (TYPE_1__*) ; 
 int /*<<< orphan*/  spiffs_api_check ; 

esp_err_t esp_spiffs_format(const char* partition_label)
{
    bool partition_was_mounted = false;
    int index;
    /* If the partition is not mounted, need to create SPIFFS structures
     * and mount the partition, unmount, format, delete SPIFFS structures.
     * See SPIFFS wiki for the reason why.
     */
    esp_err_t err = esp_spiffs_by_label(partition_label, &index);
    if (err != ESP_OK) {
        esp_vfs_spiffs_conf_t conf = {
                .format_if_mount_failed = true,
                .partition_label = partition_label,
                .max_files = 1
        };
        err = esp_spiffs_init(&conf);
        if (err != ESP_OK) {
            return err;
        }
        err = esp_spiffs_by_label(partition_label, &index);
        assert(err == ESP_OK && "failed to get index of the partition just mounted");
    } else if (SPIFFS_mounted(_efs[index]->fs)) {
        partition_was_mounted = true;
    }

    SPIFFS_unmount(_efs[index]->fs);

    s32_t res = SPIFFS_format(_efs[index]->fs);
    if (res != SPIFFS_OK) {
        ESP_LOGE(TAG, "format failed, %i", SPIFFS_errno(_efs[index]->fs));
        SPIFFS_clearerr(_efs[index]->fs);
        /* If the partition was previously mounted, but format failed, don't
         * try to mount the partition back (it will probably fail). On the
         * other hand, if it was not mounted, need to clean up.
         */
        if (!partition_was_mounted) {
            esp_spiffs_free(&_efs[index]);
        }
        return ESP_FAIL;
    }

    if (partition_was_mounted) {
        res = SPIFFS_mount(_efs[index]->fs, &_efs[index]->cfg, _efs[index]->work,
                            _efs[index]->fds, _efs[index]->fds_sz, _efs[index]->cache,
                            _efs[index]->cache_sz, spiffs_api_check);
        if (res != SPIFFS_OK) {
            ESP_LOGE(TAG, "mount failed, %i", SPIFFS_errno(_efs[index]->fs));
            SPIFFS_clearerr(_efs[index]->fs);
            return ESP_FAIL;
        }
    } else {
        esp_spiffs_free(&_efs[index]);
    }
    return ESP_OK;
}