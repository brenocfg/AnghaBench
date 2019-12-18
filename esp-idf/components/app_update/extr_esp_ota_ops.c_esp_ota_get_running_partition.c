#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t address; size_t size; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/ * esp_partition_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_PARTITION_SUBTYPE_ANY ; 
 int /*<<< orphan*/  ESP_PARTITION_TYPE_APP ; 
 size_t SPI_FLASH_CACHE2PHYS_FAIL ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * esp_partition_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* esp_partition_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_partition_iterator_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * esp_partition_next (int /*<<< orphan*/ *) ; 
 size_t spi_flash_cache2phys (TYPE_1__ const* (*) ()) ; 

const esp_partition_t* esp_ota_get_running_partition(void)
{
    static const esp_partition_t *curr_partition = NULL;

    /*
     * Currently running partition is unlikely to change across reset cycle,
     * so it can be cached here, and avoid lookup on every flash write operation.
     */
    if (curr_partition != NULL) {
        return curr_partition;
    }

    /* Find the flash address of this exact function. By definition that is part
       of the currently running firmware. Then find the enclosing partition. */
    size_t phys_offs = spi_flash_cache2phys(esp_ota_get_running_partition);

    assert (phys_offs != SPI_FLASH_CACHE2PHYS_FAIL); /* indicates cache2phys lookup is buggy */

    esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_APP,
                                                     ESP_PARTITION_SUBTYPE_ANY,
                                                     NULL);
    assert(it != NULL); /* has to be at least one app partition */

    while (it != NULL) {
        const esp_partition_t *p = esp_partition_get(it);
        if (p->address <= phys_offs && p->address + p->size > phys_offs) {
            esp_partition_iterator_release(it);
            curr_partition = p;
            return p;
        }
        it = esp_partition_next(it);
    }

    abort(); /* Partition table is invalid or corrupt */
}