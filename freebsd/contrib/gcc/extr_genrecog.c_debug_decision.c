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
struct decision {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_decision_0 (struct decision*,int /*<<< orphan*/ ,int) ; 

void
debug_decision (struct decision *d)
{
  debug_decision_0 (d, 0, 1000000);
}