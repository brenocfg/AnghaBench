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
typedef  scalar_t__ tree ;
struct TYPE_2__ {int /*<<< orphan*/  cookie; int /*<<< orphan*/  (* new_value ) (scalar_t__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ const NULL_TREE ; 
 int /*<<< orphan*/  OVL_CURRENT (scalar_t__ const) ; 
 TYPE_1__ resort_data ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
resort_method_name_cmp (const void* m1_p, const void* m2_p)
{
  const tree *const m1 = (const tree *) m1_p;
  const tree *const m2 = (const tree *) m2_p;
  if (*m1 == NULL_TREE && *m2 == NULL_TREE)
    return 0;
  if (*m1 == NULL_TREE)
    return -1;
  if (*m2 == NULL_TREE)
    return 1;
  {
    tree d1 = DECL_NAME (OVL_CURRENT (*m1));
    tree d2 = DECL_NAME (OVL_CURRENT (*m2));
    resort_data.new_value (&d1, resort_data.cookie);
    resort_data.new_value (&d2, resort_data.cookie);
    if (d1 < d2)
      return -1;
  }
  return 1;
}