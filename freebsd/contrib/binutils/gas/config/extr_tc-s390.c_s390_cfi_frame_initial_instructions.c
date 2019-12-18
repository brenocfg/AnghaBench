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
 int /*<<< orphan*/  cfi_add_CFA_def_cfa (int,int) ; 
 int s390_arch_size ; 

void
s390_cfi_frame_initial_instructions ()
{
  cfi_add_CFA_def_cfa (15, s390_arch_size == 64 ? 160 : 96);
}