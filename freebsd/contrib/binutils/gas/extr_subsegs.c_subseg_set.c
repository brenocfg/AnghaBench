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
typedef  scalar_t__ subsegT ;
typedef  scalar_t__ segT ;

/* Variables and functions */
 int /*<<< orphan*/ * mri_common_symbol ; 
 scalar_t__ now_seg ; 
 scalar_t__ now_subseg ; 
 int /*<<< orphan*/  subseg_set_rest (scalar_t__,scalar_t__) ; 

void
subseg_set (segT secptr, subsegT subseg)
{
  if (! (secptr == now_seg && subseg == now_subseg))
    subseg_set_rest (secptr, subseg);
  mri_common_symbol = NULL;
}