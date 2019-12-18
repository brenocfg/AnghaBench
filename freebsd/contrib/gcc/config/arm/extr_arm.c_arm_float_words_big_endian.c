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

/* Variables and functions */
 scalar_t__ TARGET_BIG_END ; 
 scalar_t__ TARGET_FPA ; 
 scalar_t__ TARGET_MAVERICK ; 
 scalar_t__ TARGET_VFP ; 

int
arm_float_words_big_endian (void)
{
  if (TARGET_MAVERICK)
    return 0;

  /* For FPA, float words are always big-endian.  For VFP, floats words
     follow the memory system mode.  */

  if (TARGET_FPA)
    {
      return 1;
    }

  if (TARGET_VFP)
    return (TARGET_BIG_END ? 1 : 0);

  return 1;
}