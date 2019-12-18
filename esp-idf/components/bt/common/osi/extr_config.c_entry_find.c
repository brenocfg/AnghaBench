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
struct TYPE_6__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ section_t ;
typedef  int /*<<< orphan*/  list_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ entry_t ;
typedef  int /*<<< orphan*/  config_t ;

/* Variables and functions */
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 TYPE_2__* list_node (int /*<<< orphan*/  const*) ; 
 TYPE_1__* section_find (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static entry_t *entry_find(const config_t *config, const char *section, const char *key)
{
    section_t *sec = section_find(config, section);
    if (!sec) {
        return NULL;
    }

    for (const list_node_t *node = list_begin(sec->entries); node != list_end(sec->entries); node = list_next(node)) {
        entry_t *entry = list_node(node);
        if (!strcmp(entry->key, key)) {
            return entry;
        }
    }

    return NULL;
}