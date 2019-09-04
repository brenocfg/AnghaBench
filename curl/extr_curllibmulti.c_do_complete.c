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
struct connectdata {TYPE_2__* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  chunk; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_pgrsTime (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TIMER_PRETRANSFER ; 

__attribute__((used)) static void do_complete(struct connectdata *conn)
{
  conn->data->req.chunk = FALSE;
  Curl_pgrsTime(conn->data, TIMER_PRETRANSFER);
}