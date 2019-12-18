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
typedef  TYPE_1__* variable ;
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int /*<<< orphan*/  const decl; } ;

/* Variables and functions */
 scalar_t__ VARIABLE_HASH_VAL (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
variable_htab_eq (const void *x, const void *y)
{
  const variable v = (const variable) x;
  const tree decl = (const tree) y;

  return (VARIABLE_HASH_VAL (v->decl) == VARIABLE_HASH_VAL (decl));
}