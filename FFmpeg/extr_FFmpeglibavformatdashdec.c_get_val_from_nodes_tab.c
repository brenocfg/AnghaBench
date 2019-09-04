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
typedef  scalar_t__ xmlNodePtr ;

/* Variables and functions */
 char* xmlGetProp (scalar_t__,char const*) ; 

__attribute__((used)) static char *get_val_from_nodes_tab(xmlNodePtr *nodes, const int n_nodes, const char *attrname)
{
    int i;
    char *val;

    for (i = 0; i < n_nodes; ++i) {
        if (nodes[i]) {
            val = xmlGetProp(nodes[i], attrname);
            if (val)
                return val;
        }
    }

    return NULL;
}