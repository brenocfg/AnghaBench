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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int (* types_compatible_p ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  rs6000_builtin_type (int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
rs6000_builtin_type_compatible (tree t, int id)
{
  tree builtin_type;
  builtin_type = rs6000_builtin_type (id);
  if (INTEGRAL_TYPE_P (t) && INTEGRAL_TYPE_P (builtin_type))
    return true;
  else
    return lang_hooks.types_compatible_p (t, builtin_type);
}