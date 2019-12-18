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
struct TYPE_7__ {int* tcpconnect; } ;
struct connectdata {TYPE_4__* data; TYPE_3__ bits; } ;
struct FTP {int /*<<< orphan*/  transfer; } ;
struct TYPE_6__ {struct FTP* protop; } ;
struct TYPE_5__ {scalar_t__ opt_no_body; } ;
struct TYPE_8__ {TYPE_2__ req; TYPE_1__ set; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  FTPTRANSFER_INFO ; 
 int /*<<< orphan*/  FTP_QUOTE ; 
 size_t SECONDARYSOCKET ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ftp_multi_statemach (struct connectdata*,int*) ; 
 scalar_t__ ftp_state_quote (struct connectdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infof (TYPE_4__*,char*,...) ; 

__attribute__((used)) static
CURLcode ftp_perform(struct connectdata *conn,
                     bool *connected,  /* connect status after PASV / PORT */
                     bool *dophase_done)
{
  /* this is FTP and no proxy */
  CURLcode result = CURLE_OK;

  DEBUGF(infof(conn->data, "DO phase starts\n"));

  if(conn->data->set.opt_no_body) {
    /* requested no body means no transfer... */
    struct FTP *ftp = conn->data->req.protop;
    ftp->transfer = FTPTRANSFER_INFO;
  }

  *dophase_done = FALSE; /* not done yet */

  /* start the first command in the DO phase */
  result = ftp_state_quote(conn, TRUE, FTP_QUOTE);
  if(result)
    return result;

  /* run the state-machine */
  result = ftp_multi_statemach(conn, dophase_done);

  *connected = conn->bits.tcpconnect[SECONDARYSOCKET];

  infof(conn->data, "ftp_perform ends with SECONDARY: %d\n", *connected);

  if(*dophase_done)
    DEBUGF(infof(conn->data, "DO phase is complete1\n"));

  return result;
}