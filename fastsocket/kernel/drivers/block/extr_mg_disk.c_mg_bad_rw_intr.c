#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mg_host {scalar_t__ error; TYPE_1__* req; } ;
struct TYPE_2__ {scalar_t__ errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ MG_ERR_TIMEOUT ; 
 scalar_t__ MG_MAX_ERRORS ; 
 int /*<<< orphan*/  mg_end_request_cur (struct mg_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mg_bad_rw_intr(struct mg_host *host)
{
	if (host->req)
		if (++host->req->errors >= MG_MAX_ERRORS ||
		    host->error == MG_ERR_TIMEOUT)
			mg_end_request_cur(host, -EIO);
}