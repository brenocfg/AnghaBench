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
struct wbsd_host {int dummy; } ;
struct mmc_command {int* resp; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 scalar_t__ WBSD_IDX_RESP1 ; 
 scalar_t__ WBSD_IDX_RESP2 ; 
 scalar_t__ WBSD_IDX_RESP3 ; 
 scalar_t__ WBSD_IDX_RESP4 ; 
 scalar_t__ WBSD_IDX_RSPLEN ; 
 int WBSD_RSP_LONG ; 
 int wbsd_read_index (struct wbsd_host*,scalar_t__) ; 

__attribute__((used)) static inline void wbsd_get_long_reply(struct wbsd_host *host,
	struct mmc_command *cmd)
{
	int i;

	/*
	 * Correct response type?
	 */
	if (wbsd_read_index(host, WBSD_IDX_RSPLEN) != WBSD_RSP_LONG) {
		cmd->error = -EILSEQ;
		return;
	}

	for (i = 0; i < 4; i++) {
		cmd->resp[i] =
			wbsd_read_index(host, WBSD_IDX_RESP1 + i * 4) << 24;
		cmd->resp[i] |=
			wbsd_read_index(host, WBSD_IDX_RESP2 + i * 4) << 16;
		cmd->resp[i] |=
			wbsd_read_index(host, WBSD_IDX_RESP3 + i * 4) << 8;
		cmd->resp[i] |=
			wbsd_read_index(host, WBSD_IDX_RESP4 + i * 4) << 0;
	}
}