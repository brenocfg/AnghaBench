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
struct mg_host {int /*<<< orphan*/ * req; } ;

/* Variables and functions */
 scalar_t__ __blk_end_request (int /*<<< orphan*/ *,int,unsigned int) ; 

__attribute__((used)) static bool mg_end_request(struct mg_host *host, int err, unsigned int nr_bytes)
{
	if (__blk_end_request(host->req, err, nr_bytes))
		return true;

	host->req = NULL;
	return false;
}