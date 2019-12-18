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
struct TYPE_3__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ section_t ;
typedef  int /*<<< orphan*/  entry_t ;
typedef  int /*<<< orphan*/  config_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * entry_find (int /*<<< orphan*/ *,char const*,char const*) ; 
 int list_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* section_find (int /*<<< orphan*/ *,char const*) ; 

bool config_remove_key(config_t *config, const char *section, const char *key)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(key != NULL);

    section_t *sec = section_find(config, section);
    entry_t *entry = entry_find(config, section, key);
    if (!sec || !entry) {
        return false;
    }

    return list_remove(sec->entries, entry);
}