#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ftp_conn {scalar_t__ file; int /*<<< orphan*/  pp; } ;
struct TYPE_6__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_3__ proto; TYPE_2__* data; } ;
struct FTP {scalar_t__ transfer; } ;
struct TYPE_4__ {struct FTP* protop; } ;
struct TYPE_5__ {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 scalar_t__ FTPTRANSFER_INFO ; 
 int /*<<< orphan*/  FTP_SIZE ; 
 int /*<<< orphan*/  PPSENDF (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  ftp_state_rest (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_state_size(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->data->req.protop;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  if((ftp->transfer == FTPTRANSFER_INFO) && ftpc->file) {
    /* if a "head"-like request is being made (on a file) */

    /* we know ftpc->file is a valid pointer to a file name */
    PPSENDF(&ftpc->pp, "SIZE %s", ftpc->file);

    state(conn, FTP_SIZE);
  }
  else
    result = ftp_state_rest(conn);

  return result;
}