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
struct TYPE_5__ {char* label; scalar_t__ flash_chip; scalar_t__ address; scalar_t__ size; scalar_t__ encrypted; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/ * esp_partition_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * esp_partition_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* esp_partition_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_partition_iterator_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * esp_partition_next (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 

const esp_partition_t *esp_partition_verify(const esp_partition_t *partition)
{
    assert(partition != NULL);
    const char *label = (strlen(partition->label) > 0) ? partition->label : NULL;
    esp_partition_iterator_t it = esp_partition_find(partition->type,
                                                     partition->subtype,
                                                     label);
    while (it != NULL) {
        const esp_partition_t *p = esp_partition_get(it);
        /* Can't memcmp() whole structure here as padding contents may be different */
        if (p->flash_chip == partition->flash_chip
            && p->address == partition->address
            && partition->size == p->size
            && partition->encrypted == p->encrypted) {
            esp_partition_iterator_release(it);
            return p;
        }
        it = esp_partition_next(it);
    }
    esp_partition_iterator_release(it);
    return NULL;
}