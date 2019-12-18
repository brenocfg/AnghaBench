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
typedef  enum rounding { ____Placeholder_rounding } rounding ;

/* Variables and functions */
 int __dfp_rounding_mode ; 

enum rounding
__decGetRound (void)
{
  return __dfp_rounding_mode;
}