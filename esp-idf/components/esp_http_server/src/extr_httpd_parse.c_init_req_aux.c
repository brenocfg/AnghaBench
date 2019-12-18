#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resp_hdr {int dummy; } ;
struct httpd_req_aux {int /*<<< orphan*/  resp_hdrs; scalar_t__ resp_hdrs_count; scalar_t__ req_hdrs_count; scalar_t__ first_chunk_sent; scalar_t__ content_type; scalar_t__ status; scalar_t__ remaining_len; int /*<<< orphan*/  scratch; scalar_t__ sd; } ;
struct TYPE_3__ {int max_resp_headers; } ;
typedef  TYPE_1__ httpd_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_req_aux(struct httpd_req_aux *ra, httpd_config_t *config)
{
    ra->sd = 0;
    memset(ra->scratch, 0, sizeof(ra->scratch));
    ra->remaining_len = 0;
    ra->status = 0;
    ra->content_type = 0;
    ra->first_chunk_sent = 0;
    ra->req_hdrs_count = 0;
    ra->resp_hdrs_count = 0;
    memset(ra->resp_hdrs, 0, config->max_resp_headers * sizeof(struct resp_hdr));
}