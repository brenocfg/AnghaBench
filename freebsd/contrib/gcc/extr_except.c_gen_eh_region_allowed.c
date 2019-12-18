#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_3__ {scalar_t__ type_list; } ;
struct TYPE_4__ {TYPE_1__ allowed; } ;
struct eh_region {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERT_ALLOWED_EXCEPTIONS ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  add_type_for_runtime (int /*<<< orphan*/ ) ; 
 struct eh_region* gen_eh_region (int /*<<< orphan*/ ,struct eh_region*) ; 

struct eh_region *
gen_eh_region_allowed (struct eh_region *outer, tree allowed)
{
  struct eh_region *region = gen_eh_region (ERT_ALLOWED_EXCEPTIONS, outer);
  region->u.allowed.type_list = allowed;

  for (; allowed ; allowed = TREE_CHAIN (allowed))
    add_type_for_runtime (TREE_VALUE (allowed));

  return region;
}