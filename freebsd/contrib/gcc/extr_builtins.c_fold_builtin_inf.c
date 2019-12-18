#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_HAS_INFINITIES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  real_inf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
fold_builtin_inf (tree type, int warn)
{
  REAL_VALUE_TYPE real;

  /* __builtin_inff is intended to be usable to define INFINITY on all
     targets.  If an infinity is not available, INFINITY expands "to a
     positive constant of type float that overflows at translation
     time", footnote "In this case, using INFINITY will violate the
     constraint in 6.4.4 and thus require a diagnostic." (C99 7.12#4).
     Thus we pedwarn to ensure this constraint violation is
     diagnosed.  */
  if (!MODE_HAS_INFINITIES (TYPE_MODE (type)) && warn)
    pedwarn ("target format does not support infinity");

  real_inf (&real);
  return build_real (type, real);
}