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
 int /*<<< orphan*/  IPQ_COPY_NONE ; 
 int /*<<< orphan*/  __ipq_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ipq_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_disable_timestamp () ; 
 scalar_t__ peer_pid ; 

__attribute__((used)) static inline void
__ipq_reset(void)
{
	peer_pid = 0;
	net_disable_timestamp();
	__ipq_set_mode(IPQ_COPY_NONE, 0);
	__ipq_flush(NULL, 0);
}