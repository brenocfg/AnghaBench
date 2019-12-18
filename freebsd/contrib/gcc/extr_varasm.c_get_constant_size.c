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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STRING_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STRING_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_size_in_bytes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HOST_WIDE_INT
get_constant_size (tree exp)
{
  HOST_WIDE_INT size;

  size = int_size_in_bytes (TREE_TYPE (exp));
  if (TREE_CODE (exp) == STRING_CST)
    size = MAX (TREE_STRING_LENGTH (exp), size);
  return size;
}