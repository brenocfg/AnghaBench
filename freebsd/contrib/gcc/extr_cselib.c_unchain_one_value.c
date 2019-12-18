#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ addr_list; } ;
typedef  TYPE_1__ cselib_val ;

/* Variables and functions */
 int /*<<< orphan*/  cselib_val_pool ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  unchain_one_elt_list (scalar_t__*) ; 

__attribute__((used)) static void
unchain_one_value (cselib_val *v)
{
  while (v->addr_list)
    unchain_one_elt_list (&v->addr_list);

  pool_free (cselib_val_pool, v);
}