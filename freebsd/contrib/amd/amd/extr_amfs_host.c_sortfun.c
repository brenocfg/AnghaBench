#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ voidp ;
typedef  TYPE_1__* exports ;
struct TYPE_2__ {int /*<<< orphan*/  ex_dir; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sortfun(const voidp x, const voidp y)
{
  exports *a = (exports *) x;
  exports *b = (exports *) y;

  return strcmp((*a)->ex_dir, (*b)->ex_dir);
}