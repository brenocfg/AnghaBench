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
struct ftp_conn {void* wait_data_conn; } ;
struct TYPE_8__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_3__* data; TYPE_4__ proto; } ;
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_5__ {scalar_t__ wildcardmatch; } ;
struct TYPE_7__ {TYPE_2__ wildcard; TYPE_1__ state; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLWC_DONE ; 
 scalar_t__ CURLWC_SKIP ; 
 void* FALSE ; 
 scalar_t__ ftp_parse_url_path (struct connectdata*) ; 
 scalar_t__ ftp_regular_transfer (struct connectdata*,int*) ; 
 scalar_t__ wc_statemach (struct connectdata*) ; 

__attribute__((used)) static CURLcode ftp_do(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  *done = FALSE; /* default to false */
  ftpc->wait_data_conn = FALSE; /* default to no such wait */

  if(conn->data->state.wildcardmatch) {
    result = wc_statemach(conn);
    if(conn->data->wildcard.state == CURLWC_SKIP ||
      conn->data->wildcard.state == CURLWC_DONE) {
      /* do not call ftp_regular_transfer */
      return CURLE_OK;
    }
    if(result) /* error, loop or skipping the file */
      return result;
  }
  else { /* no wildcard FSM needed */
    result = ftp_parse_url_path(conn);
    if(result)
      return result;
  }

  result = ftp_regular_transfer(conn, done);

  return result;
}