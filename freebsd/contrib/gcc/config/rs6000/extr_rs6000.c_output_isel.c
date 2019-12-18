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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int GE ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GEU ; 
 int LE ; 
 int LEU ; 
 int NE ; 
 int /*<<< orphan*/  PUT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reverse_condition (int) ; 

const char *
output_isel (rtx *operands)
{
  enum rtx_code code;

  code = GET_CODE (operands[1]);
  if (code == GE || code == GEU || code == LE || code == LEU || code == NE)
    {
      PUT_CODE (operands[1], reverse_condition (code));
      return "isel %0,%3,%2,%j1";
    }
  else
    return "isel %0,%2,%3,%j1";
}