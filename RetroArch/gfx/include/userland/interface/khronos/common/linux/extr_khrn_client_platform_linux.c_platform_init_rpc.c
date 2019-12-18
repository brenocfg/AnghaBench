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
struct CLIENT_THREAD_STATE {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void platform_init_rpc(struct CLIENT_THREAD_STATE *state)
{
   assert(1);
}