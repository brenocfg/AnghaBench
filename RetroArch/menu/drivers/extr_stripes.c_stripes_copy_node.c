#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * fullpath; } ;
typedef  TYPE_1__ stripes_node_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static stripes_node_t *stripes_copy_node(const stripes_node_t *old_node)
{
   stripes_node_t *new_node = (stripes_node_t*)malloc(sizeof(*new_node));

   *new_node            = *old_node;
   new_node->fullpath   = old_node->fullpath ? strdup(old_node->fullpath) : NULL;

   return new_node;
}