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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ automatically_generated_chrec_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline tree
chrec_type (tree chrec)
{
  if (automatically_generated_chrec_p (chrec))
    return NULL_TREE;

  return TREE_TYPE (chrec);
}