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
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bsg_request_fn (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_bsg_host_dispatch ; 

__attribute__((used)) static void iscsi_bsg_request_fn(struct request_queue *q)
{
	bsg_request_fn(q, iscsi_bsg_host_dispatch, 0);
}