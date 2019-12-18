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
struct pop3_conn {scalar_t__ state; int /*<<< orphan*/  pp; } ;
struct TYPE_2__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_pp_statemach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ POP3_STOP ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static CURLcode pop3_block_statemach(struct connectdata *conn,
                                     bool disconnecting)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  while(pop3c->state != POP3_STOP && !result)
    result = Curl_pp_statemach(&pop3c->pp, TRUE, disconnecting);

  return result;
}