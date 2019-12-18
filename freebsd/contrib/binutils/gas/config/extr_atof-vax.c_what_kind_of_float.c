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
 int D_PRECISION ; 
 int F_PRECISION ; 
 int G_PRECISION ; 
 int H_PRECISION ; 

__attribute__((used)) static int			/* 0 means letter is OK.  */
what_kind_of_float (int letter,			/* In: lowercase please. What kind of float?  */
		    int *precisionP,		/* Number of 16-bit words in the float.  */
		    long *exponent_bitsP)	/* Number of exponent bits.  */
{
  int retval;

  retval = 0;
  switch (letter)
    {
    case 'f':
      *precisionP = F_PRECISION;
      *exponent_bitsP = 8;
      break;

    case 'd':
      *precisionP = D_PRECISION;
      *exponent_bitsP = 8;
      break;

    case 'g':
      *precisionP = G_PRECISION;
      *exponent_bitsP = 11;
      break;

    case 'h':
      *precisionP = H_PRECISION;
      *exponent_bitsP = 15;
      break;

    default:
      retval = 69;
      break;
    }
  return retval;
}