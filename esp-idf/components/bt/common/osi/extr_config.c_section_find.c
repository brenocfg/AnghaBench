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
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ section_t ;
typedef  int /*<<< orphan*/  list_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  sections; } ;
typedef  TYPE_2__ config_t ;

/* Variables and functions */
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 TYPE_1__* list_node (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static section_t *section_find(const config_t *config, const char *section)
{
    for (const list_node_t *node = list_begin(config->sections); node != list_end(config->sections); node = list_next(node)) {
        section_t *sec = list_node(node);
        if (!strcmp(sec->name, section)) {
            return sec;
        }
    }

    return NULL;
}