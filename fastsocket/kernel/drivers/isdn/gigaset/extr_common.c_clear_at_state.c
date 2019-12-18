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
struct at_state_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_strings (struct at_state_t*) ; 

__attribute__((used)) static void clear_at_state(struct at_state_t *at_state)
{
	free_strings(at_state);
}