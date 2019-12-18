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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  DIV 133 
 int LAST_AND_UNUSED_TREE_CODE ; 
 int MAX_EXPR ; 
#define  MINUS 132 
 int MINUS_EXPR ; 
 int MIN_EXPR ; 
#define  MULT 131 
 int MULT_EXPR ; 
#define  PLUS 130 
 int PLUS_EXPR ; 
 int RDIV_EXPR ; 
#define  SMAX 129 
#define  SMIN 128 

int
rtx_to_tree_code (enum rtx_code code)
{
  enum tree_code tcode;

  switch (code)
    {
    case PLUS:
      tcode = PLUS_EXPR;
      break;
    case MINUS:
      tcode = MINUS_EXPR;
      break;
    case MULT:
      tcode = MULT_EXPR;
      break;
    case DIV:
      tcode = RDIV_EXPR;
      break;
    case SMIN:
      tcode = MIN_EXPR;
      break;
    case SMAX:
      tcode = MAX_EXPR;
      break;
    default:
      tcode = LAST_AND_UNUSED_TREE_CODE;
      break;
    }
  return ((int) tcode);
}