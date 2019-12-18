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
struct TYPE_3__ {char const* value; } ;
typedef  TYPE_1__ entry_t ;
typedef  int /*<<< orphan*/  config_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* entry_find (int /*<<< orphan*/  const*,char const*,char const*) ; 

const char *config_get_string(const config_t *config, const char *section, const char *key, const char *def_value)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(key != NULL);

    entry_t *entry = entry_find(config, section, key);
    if (!entry) {
        return def_value;
    }

    return entry->value;
}