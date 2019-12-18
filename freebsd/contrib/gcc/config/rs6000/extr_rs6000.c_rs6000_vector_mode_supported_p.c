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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ ALTIVEC_VECTOR_MODE (int) ; 
 scalar_t__ SPE_VECTOR_MODE (int) ; 
 scalar_t__ TARGET_ALTIVEC ; 
 scalar_t__ TARGET_SPE ; 

__attribute__((used)) static bool
rs6000_vector_mode_supported_p (enum machine_mode mode)
{

  if (TARGET_SPE && SPE_VECTOR_MODE (mode))
    return true;

  else if (TARGET_ALTIVEC && ALTIVEC_VECTOR_MODE (mode))
    return true;

  else
    return false;
}