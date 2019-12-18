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
 scalar_t__ TARGET_3DNOW ; 
 scalar_t__ TARGET_MMX ; 
 scalar_t__ TARGET_SSE ; 
 scalar_t__ TARGET_SSE2 ; 
 scalar_t__ VALID_MMX_REG_MODE (int) ; 
 scalar_t__ VALID_MMX_REG_MODE_3DNOW (int) ; 
 scalar_t__ VALID_SSE2_REG_MODE (int) ; 
 scalar_t__ VALID_SSE_REG_MODE (int) ; 

__attribute__((used)) static bool
ix86_vector_mode_supported_p (enum machine_mode mode)
{
  if (TARGET_SSE && VALID_SSE_REG_MODE (mode))
    return true;
  if (TARGET_SSE2 && VALID_SSE2_REG_MODE (mode))
    return true;
  if (TARGET_MMX && VALID_MMX_REG_MODE (mode))
    return true;
  if (TARGET_3DNOW && VALID_MMX_REG_MODE_3DNOW (mode))
    return true;
  return false;
}