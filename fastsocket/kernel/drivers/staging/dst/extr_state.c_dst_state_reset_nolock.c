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
struct dst_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_state_exit_connected (struct dst_state*) ; 
 int /*<<< orphan*/  dst_state_init_connected (struct dst_state*) ; 

__attribute__((used)) static void inline dst_state_reset_nolock(struct dst_state *st)
{
	dst_state_exit_connected(st);
	dst_state_init_connected(st);
}