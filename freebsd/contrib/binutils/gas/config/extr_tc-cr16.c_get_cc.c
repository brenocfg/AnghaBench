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
 int /*<<< orphan*/ * cr16_b_cond_tab ; 
 unsigned int cr16_num_cc ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_cc (char *cc_name)
{
   unsigned int i;

   for (i = 0; i < cr16_num_cc; i++)
     if (strcmp (cc_name, cr16_b_cond_tab[i]) == 0)
       return i;

   return -1;
}