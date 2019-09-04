#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* coalition_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  termrequested; } ;

/* Variables and functions */

boolean_t
coalition_term_requested(coalition_t coal)
{
	return coal->termrequested;
}