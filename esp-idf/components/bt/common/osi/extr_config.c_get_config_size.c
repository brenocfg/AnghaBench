#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ section_t ;
typedef  int /*<<< orphan*/  list_node_t ;
struct TYPE_6__ {char* key; char* value; } ;
typedef  TYPE_2__ entry_t ;
struct TYPE_7__ {int /*<<< orphan*/  sections; } ;
typedef  TYPE_3__ config_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* list_next (int /*<<< orphan*/  const*) ; 
 scalar_t__ list_node (int /*<<< orphan*/  const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int get_config_size(const config_t *config)
{
    assert(config != NULL);

    int w_len = 0, total_size = 0;

    for (const list_node_t *node = list_begin(config->sections); node != list_end(config->sections); node = list_next(node)) {
        const section_t *section = (const section_t *)list_node(node);
        w_len = strlen(section->name) + strlen("[]\n");// format "[section->name]\n"
        total_size += w_len;

        for (const list_node_t *enode = list_begin(section->entries); enode != list_end(section->entries); enode = list_next(enode)) {
            const entry_t *entry = (const entry_t *)list_node(enode);
            w_len = strlen(entry->key) + strlen(entry->value) + strlen(" = \n");// format "entry->key = entry->value\n"
            total_size += w_len;
        }

        // Only add a separating newline if there are more sections.
        if (list_next(node) != list_end(config->sections)) {
                total_size ++;  //'\n'
        } else {
            break;
        }
    }
    total_size ++; //'\0'
    return total_size;
}