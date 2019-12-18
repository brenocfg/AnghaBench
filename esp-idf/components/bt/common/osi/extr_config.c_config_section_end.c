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
struct TYPE_3__ {int /*<<< orphan*/  sections; } ;
typedef  TYPE_1__ config_t ;
typedef  int /*<<< orphan*/  config_section_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ list_end (int /*<<< orphan*/ ) ; 

const config_section_node_t *config_section_end(const config_t *config)
{
    assert(config != NULL);
    return (const config_section_node_t *)list_end(config->sections);
}