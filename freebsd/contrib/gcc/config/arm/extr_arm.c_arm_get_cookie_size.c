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
 int /*<<< orphan*/  TARGET_AAPCS_BASED ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  default_cxx_get_cookie_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sizetype ; 

__attribute__((used)) static tree
arm_get_cookie_size (tree type)
{
  tree size;

  if (!TARGET_AAPCS_BASED)
    return default_cxx_get_cookie_size (type);

  size = build_int_cst (sizetype, 8);
  return size;
}