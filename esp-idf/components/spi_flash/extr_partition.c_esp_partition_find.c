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
typedef  int /*<<< orphan*/  esp_partition_type_t ;
typedef  int /*<<< orphan*/  esp_partition_subtype_t ;
typedef  int /*<<< orphan*/ * esp_partition_iterator_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 scalar_t__ ensure_partitions_loaded () ; 
 int /*<<< orphan*/ * esp_partition_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iterator_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

esp_partition_iterator_t esp_partition_find(esp_partition_type_t type,
        esp_partition_subtype_t subtype, const char* label)
{
    if (ensure_partitions_loaded() != ESP_OK) {
        return NULL;
    }
    // create an iterator pointing to the start of the list
    // (next item will be the first one)
    esp_partition_iterator_t it = iterator_create(type, subtype, label);
    // advance iterator to the next item which matches constraints
    it = esp_partition_next(it);
    // if nothing found, it == NULL and iterator has been released
    return it;
}