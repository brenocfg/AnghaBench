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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  IS_EMPTY_STMT (scalar_t__) ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static inline bool
is_exec_stmt (tree t)
{
  return (t && !IS_EMPTY_STMT (t) && t != error_mark_node);
}