#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request_queue {struct mg_host* queuedata; } ;
struct mg_host {TYPE_1__* req; } ;
struct TYPE_5__ {scalar_t__ cmd_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ READ ; 
 scalar_t__ REQ_TYPE_FS ; 
 TYPE_1__* blk_fetch_request (struct request_queue*) ; 
 int /*<<< orphan*/  mg_end_request_cur (struct mg_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_read (TYPE_1__*) ; 
 int /*<<< orphan*/  mg_write (TYPE_1__*) ; 
 scalar_t__ rq_data_dir (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mg_request_poll(struct request_queue *q)
{
	struct mg_host *host = q->queuedata;

	while (1) {
		if (!host->req) {
			host->req = blk_fetch_request(q);
			if (!host->req)
				break;
		}

		if (unlikely(host->req->cmd_type != REQ_TYPE_FS)) {
			mg_end_request_cur(host, -EIO);
			continue;
		}

		if (rq_data_dir(host->req) == READ)
			mg_read(host->req);
		else
			mg_write(host->req);
	}
}