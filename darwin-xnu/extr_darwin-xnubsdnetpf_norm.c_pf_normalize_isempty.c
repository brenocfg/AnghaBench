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
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_cachequeue ; 
 int /*<<< orphan*/  pf_fragqueue ; 

int
pf_normalize_isempty(void)
{
	return (TAILQ_EMPTY(&pf_fragqueue) && TAILQ_EMPTY(&pf_cachequeue));
}