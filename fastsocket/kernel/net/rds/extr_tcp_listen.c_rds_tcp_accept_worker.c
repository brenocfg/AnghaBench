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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ rds_tcp_accept_one (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_tcp_listen_sock ; 

__attribute__((used)) static void rds_tcp_accept_worker(struct work_struct *work)
{
	while (rds_tcp_accept_one(rds_tcp_listen_sock) == 0)
		cond_resched();
}