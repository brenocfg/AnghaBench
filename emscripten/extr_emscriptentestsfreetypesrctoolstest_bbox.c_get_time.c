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
 long CLOCKS_PER_SEC ; 
 long clock () ; 

__attribute__((used)) static long
  get_time( void )
  {
    return clock() * 10000L / CLOCKS_PER_SEC;
  }