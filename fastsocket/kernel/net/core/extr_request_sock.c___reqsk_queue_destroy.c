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
struct request_sock_queue {struct listen_sock* listen_opt; } ;
struct request_sock {int dummy; } ;
struct listen_sock {int nr_table_entries; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (struct listen_sock*) ; 
 int /*<<< orphan*/  vfree (struct listen_sock*) ; 

void __reqsk_queue_destroy(struct request_sock_queue *queue)
{
	struct listen_sock *lopt;
	size_t lopt_size;

	/*
	 * this is an error recovery path only
	 * no locking needed and the lopt is not NULL
	 */

	lopt = queue->listen_opt;
	lopt_size = sizeof(struct listen_sock) +
		lopt->nr_table_entries * sizeof(struct request_sock *);

	if (lopt_size > PAGE_SIZE)
		vfree(lopt);
	else
		kfree(lopt);
}