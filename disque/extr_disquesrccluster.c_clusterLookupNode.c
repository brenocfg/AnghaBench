#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dictEntry ;
typedef  int /*<<< orphan*/  clusterNode ;
struct TYPE_4__ {TYPE_1__* cluster; } ;
struct TYPE_3__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dictGetVal (int /*<<< orphan*/ *) ; 
 TYPE_2__ server ; 

clusterNode *clusterLookupNode(char *name) {
    dictEntry *de = dictFind(server.cluster->nodes,name);
    if (de == NULL) return NULL;
    return dictGetVal(de);
}