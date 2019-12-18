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
typedef  TYPE_1__* mfsplay_tree_node ;
typedef  int /*<<< orphan*/  __mf_object_t ;
struct TYPE_3__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mf_describe_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
__mf_report_leaks_fn (mfsplay_tree_node n, void *param)
{
  __mf_object_t *node = (__mf_object_t *) n->value;
  unsigned *count = (unsigned *) param;

  if (count != NULL)
    (*count) ++;

  fprintf (stderr, "Leaked object %u:\n", (*count));
  __mf_describe_object (node);

  return 0;
}