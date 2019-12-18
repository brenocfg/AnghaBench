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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int ix86_fp_comparison_arithmetics_cost (int) ; 
 int ix86_fp_comparison_fcomi_cost (int) ; 
 int ix86_fp_comparison_sahf_cost (int) ; 

__attribute__((used)) static int
ix86_fp_comparison_cost (enum rtx_code code)
{
  int fcomi_cost, sahf_cost, arithmetics_cost = 1024;
  int min;

  fcomi_cost = ix86_fp_comparison_fcomi_cost (code);
  sahf_cost = ix86_fp_comparison_sahf_cost (code);

  min = arithmetics_cost = ix86_fp_comparison_arithmetics_cost (code);
  if (min > sahf_cost)
    min = sahf_cost;
  if (min > fcomi_cost)
    min = fcomi_cost;
  return min;
}