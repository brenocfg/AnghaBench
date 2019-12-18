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

/* Variables and functions */
 int /*<<< orphan*/  __MF_TYPE_HEAP ; 
 int /*<<< orphan*/  __MF_TYPE_HEAP_I ; 
 int /*<<< orphan*/  __mf_object_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mf_report_leaks_fn ; 
 int /*<<< orphan*/  mfsplay_tree_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned
__mf_report_leaks ()
{
  unsigned count = 0;

  (void) mfsplay_tree_foreach (__mf_object_tree (__MF_TYPE_HEAP),
                             __mf_report_leaks_fn, & count);
  (void) mfsplay_tree_foreach (__mf_object_tree (__MF_TYPE_HEAP_I),
                             __mf_report_leaks_fn, & count);

  return count;
}