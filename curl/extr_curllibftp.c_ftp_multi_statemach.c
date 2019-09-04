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
struct ftp_conn {scalar_t__ state; int /*<<< orphan*/  pp; } ;
struct TYPE_2__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_pp_statemach (int /*<<< orphan*/ *,int,int) ; 
 int FALSE ; 
 scalar_t__ FTP_STOP ; 
 int TRUE ; 

__attribute__((used)) static CURLcode ftp_multi_statemach(struct connectdata *conn,
                                    bool *done)
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  CURLcode result = Curl_pp_statemach(&ftpc->pp, FALSE, FALSE);

  /* Check for the state outside of the Curl_socket_check() return code checks
     since at times we are in fact already in this state when this function
     gets called. */
  *done = (ftpc->state == FTP_STOP) ? TRUE : FALSE;

  return result;
}