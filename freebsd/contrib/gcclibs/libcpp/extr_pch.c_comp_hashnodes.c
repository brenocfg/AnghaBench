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
typedef  int /*<<< orphan*/  cpp_hashnode ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_NAME (int /*<<< orphan*/ *) ; 
 int ustrcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
comp_hashnodes (const void *px, const void *py)
{
  cpp_hashnode *x = *(cpp_hashnode **) px;
  cpp_hashnode *y = *(cpp_hashnode **) py;
  return ustrcmp (NODE_NAME (x), NODE_NAME (y));
}