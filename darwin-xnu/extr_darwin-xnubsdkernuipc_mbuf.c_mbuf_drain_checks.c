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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ mb_drain_maxint ; 
 scalar_t__ mb_waiters ; 

__attribute__((used)) static int
mbuf_drain_checks(boolean_t ignore_waiters)
{

	if (mb_drain_maxint == 0)
		return 0;
	if (!ignore_waiters && mb_waiters != 0)
		return 0;

	return 1;
}