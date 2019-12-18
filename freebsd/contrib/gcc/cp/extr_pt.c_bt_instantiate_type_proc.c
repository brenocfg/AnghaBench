#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* binding_entry ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSTYPE_TI_ARGS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_AGGR_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_type_instantiation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uses_template_parms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bt_instantiate_type_proc (binding_entry entry, void *data)
{
  tree storage = *(tree *) data;

  if (IS_AGGR_TYPE (entry->type)
      && !uses_template_parms (CLASSTYPE_TI_ARGS (entry->type)))
    do_type_instantiation (TYPE_MAIN_DECL (entry->type), storage, 0);
}