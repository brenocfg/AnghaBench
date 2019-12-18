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
typedef  int /*<<< orphan*/  config_section_node_t ;
typedef  int /*<<< orphan*/  btc_config_section_iter_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * config ; 
 char const* config_section_name (int /*<<< orphan*/  const*) ; 

const char *btc_config_section_name(const btc_config_section_iter_t *section)
{
    assert(config != NULL);
    assert(section != NULL);
    return config_section_name((const config_section_node_t *)section);
}