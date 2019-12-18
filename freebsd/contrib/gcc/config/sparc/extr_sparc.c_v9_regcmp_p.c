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
 int EQ ; 
 int GE ; 
 int GT ; 
 int LE ; 
 int LT ; 
 int NE ; 

int
v9_regcmp_p (enum rtx_code code)
{
  return (code == EQ || code == NE || code == GE || code == LT
	  || code == LE || code == GT);
}