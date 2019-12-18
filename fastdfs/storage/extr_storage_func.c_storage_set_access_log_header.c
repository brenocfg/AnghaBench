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
struct log_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STORAGE_ACCESS_HEADER_LEN ; 
 int /*<<< orphan*/  STORAGE_ACCESS_HEADER_STR ; 
 int /*<<< orphan*/  log_header (struct log_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void storage_set_access_log_header(struct log_context *pContext)
{
#define STORAGE_ACCESS_HEADER_STR "client_ip action filename status time_used_ms req_len resp_len"
#define STORAGE_ACCESS_HEADER_LEN (sizeof(STORAGE_ACCESS_HEADER_STR) - 1)

    log_header(pContext, STORAGE_ACCESS_HEADER_STR, STORAGE_ACCESS_HEADER_LEN);
}