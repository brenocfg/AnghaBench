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
struct TYPE_3__ {scalar_t__ ignore_sess_ctx_changes; scalar_t__ free_ctx; scalar_t__ sess_ctx; scalar_t__ user_ctx; scalar_t__ aux; scalar_t__ content_len; scalar_t__ uri; scalar_t__ method; scalar_t__ handle; } ;
typedef  TYPE_1__ httpd_req_t ;
typedef  int /*<<< orphan*/  httpd_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_req(httpd_req_t *r, httpd_config_t *config)
{
    r->handle = 0;
    r->method = 0;
    memset((char*)r->uri, 0, sizeof(r->uri));
    r->content_len = 0;
    r->aux = 0;
    r->user_ctx = 0;
    r->sess_ctx = 0;
    r->free_ctx = 0;
    r->ignore_sess_ctx_changes = 0;
}