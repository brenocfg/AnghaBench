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
typedef  int /*<<< orphan*/  config_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * entry_find (int /*<<< orphan*/  const*,char const*,char const*) ; 

bool config_has_key(const config_t *config, const char *section, const char *key)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(key != NULL);

    return (entry_find(config, section, key) != NULL);
}