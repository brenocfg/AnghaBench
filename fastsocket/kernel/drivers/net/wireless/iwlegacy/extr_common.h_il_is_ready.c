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
struct il_priv {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_EXIT_PENDING ; 
 int /*<<< orphan*/  S_GEO_CONFIGURED ; 
 int /*<<< orphan*/  S_READY ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
il_is_ready(struct il_priv *il)
{
	/* The adapter is 'ready' if READY and GEO_CONFIGURED bits are
	 * set but EXIT_PENDING is not */
	return test_bit(S_READY, &il->status) &&
	    test_bit(S_GEO_CONFIGURED, &il->status) &&
	    !test_bit(S_EXIT_PENDING, &il->status);
}