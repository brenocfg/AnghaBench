#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* partition; scalar_t__ by_label; } ;
typedef  TYPE_2__ esp_spiffs_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int CONFIG_SPIFFS_MAX_PARTITIONS ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__** _efs ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t esp_spiffs_by_label(const char* label, int * index){
    int i;
    esp_spiffs_t * p;
    for (i = 0; i < CONFIG_SPIFFS_MAX_PARTITIONS; i++) {
        p = _efs[i];
        if (p) {
            if (!label && !p->by_label) {
                *index = i;
                return ESP_OK;
            }
            if (label && p->by_label && strncmp(label, p->partition->label, 17) == 0) {
                *index = i;
                return ESP_OK;
            }
        }
    }
    return ESP_ERR_NOT_FOUND;
}