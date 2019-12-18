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
typedef  int /*<<< orphan*/  pst_syms_struct ;

/* Variables and functions */
 int /*<<< orphan*/ * pst_syms_array ; 
 scalar_t__ pst_syms_count ; 
 int pst_syms_size ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
init_pst_syms (void)
{
  pst_syms_count = 0;
  pst_syms_size = 20;
  pst_syms_array = (pst_syms_struct *) xmalloc (20 * sizeof (pst_syms_struct));
}