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
struct floatformat {int totalsize; } ;

/* Variables and functions */
 int TARGET_CHAR_BIT ; 
 int TARGET_DOUBLE_BIT ; 
 struct floatformat const* TARGET_DOUBLE_FORMAT ; 
 int TARGET_FLOAT_BIT ; 
 struct floatformat const* TARGET_FLOAT_FORMAT ; 
 int TARGET_LONG_DOUBLE_BIT ; 
 struct floatformat const* TARGET_LONG_DOUBLE_FORMAT ; 

__attribute__((used)) static const struct floatformat *
floatformat_from_length (int len)
{
  if (len * TARGET_CHAR_BIT == TARGET_FLOAT_BIT)
    return TARGET_FLOAT_FORMAT;
  else if (len * TARGET_CHAR_BIT == TARGET_DOUBLE_BIT)
    return TARGET_DOUBLE_FORMAT;
  else if (len * TARGET_CHAR_BIT == TARGET_LONG_DOUBLE_BIT)
    return TARGET_LONG_DOUBLE_FORMAT;
  /* On i386 the 'long double' type takes 96 bits,
     while the real number of used bits is only 80,
     both in processor and in memory.  
     The code below accepts the real bit size.  */ 
  else if ((TARGET_LONG_DOUBLE_FORMAT != NULL) 
	   && (len * TARGET_CHAR_BIT ==
               TARGET_LONG_DOUBLE_FORMAT->totalsize))
    return TARGET_LONG_DOUBLE_FORMAT;

  return NULL;
}