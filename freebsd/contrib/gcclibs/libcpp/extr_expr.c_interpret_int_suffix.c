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
 unsigned int CPP_N_IMAGINARY ; 
 unsigned int CPP_N_LARGE ; 
 unsigned int CPP_N_MEDIUM ; 
 unsigned int CPP_N_SMALL ; 
 unsigned int CPP_N_UNSIGNED ; 

__attribute__((used)) static unsigned int
interpret_int_suffix (const uchar *s, size_t len)
{
  size_t u, l, i;

  u = l = i = 0;

  while (len--)
    switch (s[len])
      {
      case 'u': case 'U':	u++; break;
      case 'i': case 'I':
      case 'j': case 'J':	i++; break;
      case 'l': case 'L':	l++;
	/* If there are two Ls, they must be adjacent and the same case.  */
	if (l == 2 && s[len] != s[len + 1])
	  return 0;
	break;
      default:
	return 0;
      }

  if (l > 2 || u > 1 || i > 1)
    return 0;

  return ((i ? CPP_N_IMAGINARY : 0)
	  | (u ? CPP_N_UNSIGNED : 0)
	  | ((l == 0) ? CPP_N_SMALL
	     : (l == 1) ? CPP_N_MEDIUM : CPP_N_LARGE));
}