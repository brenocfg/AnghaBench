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
typedef  int /*<<< orphan*/  hashval_t ;
struct TYPE_2__ {int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 int /*<<< orphan*/  VARIABLE_HASH_VAL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
variable_htab_hash (const void *x)
{
  const variable v = (const variable) x;

  return (VARIABLE_HASH_VAL (v->decl));
}