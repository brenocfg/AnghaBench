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
 scalar_t__ CLOCKS_PER_SEC ; 
 scalar_t__ clock () ; 

double cpu_time ( void )

/******************************************************************************/
/*
  Purpose:

    CPU_TIME returns the current reading on the CPU clock.

  Discussion:

    The CPU time measurements available through this routine are often
    not very accurate.  In some cases, the accuracy is no better than
    a hundredth of a second.  

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    06 June 2005

  Author:

    John Burkardt

  Parameters:

    Output, double CPU_TIME, the current reading of the CPU clock, in seconds.
*/
{
  double value;

  value = ( double ) clock ( ) 
        / ( double ) CLOCKS_PER_SEC;

  return value;
}