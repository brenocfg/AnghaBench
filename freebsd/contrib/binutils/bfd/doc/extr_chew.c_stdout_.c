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
 int /*<<< orphan*/  icheck_range () ; 
 int* isp ; 
 int /*<<< orphan*/  pc ; 

__attribute__((used)) static void
stdout_ ()
{
  isp++;
  icheck_range ();
  *isp = 1;
  pc++;
}