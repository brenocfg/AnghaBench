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
struct TYPE_2__ {int uid; } ;
typedef  TYPE_1__ uid2home_t ;

/* Variables and functions */

__attribute__((used)) static int
plt_compare_fxn(const voidp x, const voidp y)

{
  uid2home_t *i = (uid2home_t *) x;
  uid2home_t *j = (uid2home_t *) y;

  return i->uid - j->uid;
}