#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ section_t ;
typedef  int /*<<< orphan*/  list_node_t ;
typedef  TYPE_1__ entry_t ;
struct TYPE_13__ {int /*<<< orphan*/  sections; } ;
typedef  TYPE_3__ config_t ;

/* Variables and functions */
 TYPE_1__* entry_new (char const*,char const*) ; 
 int /*<<< orphan*/  list_append (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 TYPE_1__* list_node (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  list_prepend (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_strdup (char const*) ; 
 TYPE_1__* section_find (TYPE_3__*,char const*) ; 
 TYPE_1__* section_new (char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

void config_set_string(config_t *config, const char *section, const char *key, const char *value, bool insert_back)
{
    section_t *sec = section_find(config, section);
    if (!sec) {
        sec = section_new(section);
        if (insert_back) {
            list_append(config->sections, sec);
        } else {
            list_prepend(config->sections, sec);
        }
    }

    for (const list_node_t *node = list_begin(sec->entries); node != list_end(sec->entries); node = list_next(node)) {
        entry_t *entry = list_node(node);
        if (!strcmp(entry->key, key)) {
            osi_free(entry->value);
            entry->value = osi_strdup(value);
            return;
        }
    }

    entry_t *entry = entry_new(key, value);
    list_append(sec->entries, entry);
}