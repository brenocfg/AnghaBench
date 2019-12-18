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
 int alpha_auto_align_on ; 
 int /*<<< orphan*/  cons (int) ; 

__attribute__((used)) static void
s_alpha_ucons (int bytes)
{
  int hold = alpha_auto_align_on;
  alpha_auto_align_on = 0;
  cons (bytes);
  alpha_auto_align_on = hold;
}