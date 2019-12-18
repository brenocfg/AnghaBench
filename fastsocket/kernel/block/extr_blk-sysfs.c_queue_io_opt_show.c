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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  queue_io_opt (struct request_queue*) ; 
 int /*<<< orphan*/  queue_var_show (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t queue_io_opt_show(struct request_queue *q, char *page)
{
	return queue_var_show(queue_io_opt(q), page);
}