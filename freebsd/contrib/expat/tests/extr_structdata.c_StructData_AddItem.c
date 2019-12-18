#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XML_Char ;
struct TYPE_7__ {size_t count; size_t max_count; TYPE_1__* entries; } ;
struct TYPE_6__ {int data0; int data1; int data2; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ StructDataEntry ;
typedef  TYPE_2__ StructData ;

/* Variables and functions */
 scalar_t__ STRUCT_EXTENSION_COUNT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xmlstrdup (int /*<<< orphan*/  const*) ; 

void
StructData_AddItem(StructData *storage,
                   const XML_Char *s,
                   int data0,
                   int data1,
                   int data2)
{
    StructDataEntry *entry;

    assert(storage != NULL);
    assert(s != NULL);
    if (storage->count == storage->max_count) {
        StructDataEntry *new;

        storage->max_count += STRUCT_EXTENSION_COUNT;
        new = realloc(storage->entries,
                      storage->max_count * sizeof(StructDataEntry));
        assert(new != NULL);
        storage->entries = new;
    }

    entry = &storage->entries[storage->count];
    entry->str = xmlstrdup(s);
    entry->data0 = data0;
    entry->data1 = data1;
    entry->data2 = data2;
    storage->count++;
}