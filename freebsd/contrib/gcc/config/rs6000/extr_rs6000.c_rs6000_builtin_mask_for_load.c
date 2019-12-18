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
 scalar_t__ TARGET_ALTIVEC ; 
 int /*<<< orphan*/  altivec_builtin_mask_for_load ; 

__attribute__((used)) static tree
rs6000_builtin_mask_for_load (void)
{
  if (TARGET_ALTIVEC)
    return altivec_builtin_mask_for_load;
  else
    return 0;
}