#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* tcpconnect; } ;
struct connectdata {TYPE_4__* data; TYPE_2__ bits; } ;
struct POP3 {int /*<<< orphan*/  transfer; } ;
struct TYPE_5__ {scalar_t__ opt_no_body; } ;
struct TYPE_7__ {struct POP3* protop; } ;
struct TYPE_8__ {TYPE_1__ set; TYPE_3__ req; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 size_t FIRSTSOCKET ; 
 int /*<<< orphan*/  FTPTRANSFER_INFO ; 
 int /*<<< orphan*/  infof (TYPE_4__*,char*) ; 
 scalar_t__ pop3_multi_statemach (struct connectdata*,int*) ; 
 scalar_t__ pop3_perform_command (struct connectdata*) ; 

__attribute__((used)) static CURLcode pop3_perform(struct connectdata *conn, bool *connected,
                             bool *dophase_done)
{
  /* This is POP3 and no proxy */
  CURLcode result = CURLE_OK;
  struct POP3 *pop3 = conn->data->req.protop;

  DEBUGF(infof(conn->data, "DO phase starts\n"));

  if(conn->data->set.opt_no_body) {
    /* Requested no body means no transfer */
    pop3->transfer = FTPTRANSFER_INFO;
  }

  *dophase_done = FALSE; /* not done yet */

  /* Start the first command in the DO phase */
  result = pop3_perform_command(conn);
  if(result)
    return result;

  /* Run the state-machine */
  result = pop3_multi_statemach(conn, dophase_done);

  *connected = conn->bits.tcpconnect[FIRSTSOCKET];

  if(*dophase_done)
    DEBUGF(infof(conn->data, "DO phase is complete\n"));

  return result;
}