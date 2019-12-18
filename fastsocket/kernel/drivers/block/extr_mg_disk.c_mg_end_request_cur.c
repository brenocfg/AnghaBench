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
struct mg_host {int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_cur_bytes (int /*<<< orphan*/ ) ; 
 int mg_end_request (struct mg_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mg_end_request_cur(struct mg_host *host, int err)
{
	return mg_end_request(host, err, blk_rq_cur_bytes(host->req));
}