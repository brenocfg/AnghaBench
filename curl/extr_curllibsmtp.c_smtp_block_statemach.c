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
struct smtp_conn {scalar_t__ state; int /*<<< orphan*/  pp; } ;
struct TYPE_2__ {struct smtp_conn smtpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_pp_statemach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SMTP_STOP ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static CURLcode smtp_block_statemach(struct connectdata *conn,
                                     bool disconnecting)
{
  CURLcode result = CURLE_OK;
  struct smtp_conn *smtpc = &conn->proto.smtpc;

  while(smtpc->state != SMTP_STOP && !result)
    result = Curl_pp_statemach(&smtpc->pp, TRUE, disconnecting);

  return result;
}