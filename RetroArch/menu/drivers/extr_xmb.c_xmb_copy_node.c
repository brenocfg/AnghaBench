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
typedef  TYPE_1__ xmb_node_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmb_node_t *xmb_copy_node(const xmb_node_t *old_node)
{
   xmb_node_t *new_node = (xmb_node_t*)malloc(sizeof(*new_node));

   if (!new_node)
      return NULL;

   *new_node            = *old_node;
   new_node->fullpath   = old_node->fullpath ? strdup(old_node->fullpath) : NULL;

   return new_node;
}