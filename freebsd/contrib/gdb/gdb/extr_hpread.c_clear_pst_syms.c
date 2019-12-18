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
 scalar_t__ pst_syms_array ; 
 scalar_t__ pst_syms_count ; 
 scalar_t__ pst_syms_size ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 

__attribute__((used)) static void
clear_pst_syms (void)
{
  pst_syms_count = 0;
  pst_syms_size = 0;
  xfree (pst_syms_array);
  pst_syms_array = 0;
}