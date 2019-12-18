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
 int MAX_XPAIRS_INCREMENT ; 
 scalar_t__ chk ; 
 int current_max_xpairs ; 
 int /*<<< orphan*/  num_reallocs ; 
 scalar_t__ nxt ; 
 scalar_t__ reallocate_integer_array (scalar_t__,int) ; 
 int /*<<< orphan*/  zero_out (char*,size_t) ; 

void    expand_nxt_chk ()
{
	int old_max = current_max_xpairs;

	current_max_xpairs += MAX_XPAIRS_INCREMENT;

	++num_reallocs;

	nxt = reallocate_integer_array (nxt, current_max_xpairs);
	chk = reallocate_integer_array (chk, current_max_xpairs);

	zero_out ((char *) (chk + old_max),
		  (size_t) (MAX_XPAIRS_INCREMENT * sizeof (int)));
}