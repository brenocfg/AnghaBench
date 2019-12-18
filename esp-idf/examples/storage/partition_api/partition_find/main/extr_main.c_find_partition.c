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
typedef  int /*<<< orphan*/  esp_partition_type_t ;
struct TYPE_3__ {char* size; int /*<<< orphan*/  address; int /*<<< orphan*/  label; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_partition_subtype_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* esp_partition_find_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  get_subtype_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_type_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_partition(esp_partition_type_t type, esp_partition_subtype_t subtype, const char* name)
{
    ESP_LOGI(TAG, "Find partition with type %s, subtype %s, label %s...", get_type_str(type), get_subtype_str(subtype),
                    name == NULL ? "NULL (unspecified)" : name);
    const esp_partition_t * part  = esp_partition_find_first(type, subtype, name); 
    ESP_LOGI(TAG, "\tfound partition '%s' at offset 0x%x with size 0x%x", part->label, part->address, part->size); 
}