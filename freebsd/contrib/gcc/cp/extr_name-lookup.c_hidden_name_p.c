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

/* Variables and functions */
 scalar_t__ DECL_ANTICIPATED (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_LANG_SPECIFIC (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 

bool
hidden_name_p (tree val)
{
  if (DECL_P (val)
      && DECL_LANG_SPECIFIC (val)
      && DECL_ANTICIPATED (val))
    return true;
  return false;
}