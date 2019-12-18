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
struct TYPE_2__ {scalar_t__ (* builtin_function ) (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILT_IN_MD ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_1__ lang_hooks ; 
 scalar_t__* rs6000_builtin_decls ; 
 scalar_t__ stub1 (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int target_flags ; 

__attribute__((used)) static void
def_builtin (int mask, const char *name, tree type, int code)
{
  if (mask & target_flags)
    {
      if (rs6000_builtin_decls[code])
	abort ();

      rs6000_builtin_decls[code] =
        lang_hooks.builtin_function (name, type, code, BUILT_IN_MD,
				     NULL, NULL_TREE);
    }
}