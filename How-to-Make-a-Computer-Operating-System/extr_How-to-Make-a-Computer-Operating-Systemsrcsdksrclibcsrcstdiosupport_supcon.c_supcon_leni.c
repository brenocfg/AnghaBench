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

int  supcon_leni(int num)
{
  int p;
  int sign;

      if ( num < 0 ) 
      {
        p = -num;
      	sign = 1;
      }
      else
      {
        p = num;
      	sign = 0;
      }
  
	if ( p < 10 ) return sign + 1;
	if ( p < 100 ) return sign + 2;
	if ( p < 1000 ) return sign + 3;
	if ( p < 10000 ) return sign + 4;
	if ( p < 100000 ) return sign + 5;
	if ( p < 1000000 ) return sign + 6;
	if ( p < 10000000 ) return sign + 7;
	if ( p < 100000000 ) return sign + 8;
	if ( p < 1000000000 ) return sign + 9;

  return 10;
}