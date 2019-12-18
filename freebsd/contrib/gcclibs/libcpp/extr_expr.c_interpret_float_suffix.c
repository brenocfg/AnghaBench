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
typedef  int uchar ;

/* Variables and functions */
 unsigned int CPP_N_DEFAULT ; 
 unsigned int CPP_N_DFLOAT ; 
 unsigned int CPP_N_IMAGINARY ; 
 unsigned int CPP_N_LARGE ; 
 unsigned int CPP_N_MEDIUM ; 
 unsigned int CPP_N_SMALL ; 

__attribute__((used)) static unsigned int
interpret_float_suffix (const uchar *s, size_t len)
{
  size_t f = 0, l = 0, i = 0, d = 0, d0 = 0;

  while (len--)
    switch (s[len])
      {
      case 'f': case 'F':
	if (d > 0)
	  return 0;
	f++;
	break;
      case 'l': case 'L':
	if (d > 0)
	  return 0;
	l++;
	break;
      case 'i': case 'I':
      case 'j': case 'J': i++; break;
      case 'd': case 'D': d++; break;
      default:
	return 0;
      }

  if (d == 1 && !f && !l) {
    d = 0;
    d0 = 1;
  }

  if (f + d0 + l > 1 || i > 1)
    return 0;

  /* Allow dd, df, dl suffixes for decimal float constants.  */
  if (d && ((d + f + l != 2) || i))
    return 0;

  return ((i ? CPP_N_IMAGINARY : 0)
	  | (f ? CPP_N_SMALL :
	     d0 ? CPP_N_MEDIUM :
	     l ? CPP_N_LARGE : CPP_N_DEFAULT)
	  | (d ? CPP_N_DFLOAT : 0));
}