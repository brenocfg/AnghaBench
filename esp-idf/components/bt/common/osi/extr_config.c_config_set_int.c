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
 int /*<<< orphan*/  config_set_string (int /*<<< orphan*/ *,char const*,char const*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void config_set_int(config_t *config, const char *section, const char *key, int value)
{
    assert(config != NULL);
    assert(section != NULL);
    assert(key != NULL);

    char value_str[32] = { 0 };
    sprintf(value_str, "%d", value);
    config_set_string(config, section, key, value_str, false);
}