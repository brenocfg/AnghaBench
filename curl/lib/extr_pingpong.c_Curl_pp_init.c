#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pingpong {int /*<<< orphan*/  response; int /*<<< orphan*/  pending_resp; int /*<<< orphan*/  linestart_resp; scalar_t__ nread_resp; struct connectdata* conn; } ;
struct connectdata {TYPE_2__* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_4__ {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_now () ; 
 int /*<<< orphan*/  TRUE ; 

void Curl_pp_init(struct pingpong *pp)
{
  struct connectdata *conn = pp->conn;
  pp->nread_resp = 0;
  pp->linestart_resp = conn->data->state.buffer;
  pp->pending_resp = TRUE;
  pp->response = Curl_now(); /* start response time-out now! */
}