#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int SPIFFS_mounted (int /*<<< orphan*/ ) ; 
 TYPE_1__** _efs ; 
 scalar_t__ esp_spiffs_by_label (char const*,int*) ; 

bool esp_spiffs_mounted(const char* partition_label)
{
    int index;
    if (esp_spiffs_by_label(partition_label, &index) != ESP_OK) {
        return false;
    }
    return (SPIFFS_mounted(_efs[index]->fs));
}