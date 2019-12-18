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
 int /*<<< orphan*/  s_comm_internal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_lcomm_internal ; 

void
s_lcomm (int needs_align)
{
  s_comm_internal (needs_align, s_lcomm_internal);
}