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
struct ftp_conn {scalar_t__ file; } ;
struct TYPE_4__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_1__ proto; struct Curl_easy* data; } ;
struct FTP {int /*<<< orphan*/  transfer; } ;
struct TYPE_5__ {int /*<<< orphan*/  prefer_ascii; scalar_t__ opt_no_body; } ;
struct TYPE_6__ {struct FTP* protop; } ;
struct Curl_easy {TYPE_2__ set; TYPE_3__ req; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  FTPTRANSFER_INFO ; 
 int /*<<< orphan*/  FTP_TYPE ; 
 scalar_t__ ftp_nb_type (struct connectdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftp_need_type (struct connectdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ ftp_state_size (struct connectdata*) ; 

__attribute__((used)) static CURLcode ftp_state_type(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct FTP *ftp = conn->data->req.protop;
  struct Curl_easy *data = conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  /* If we have selected NOBODY and HEADER, it means that we only want file
     information. Which in FTP can't be much more than the file size and
     date. */
  if(data->set.opt_no_body && ftpc->file &&
     ftp_need_type(conn, data->set.prefer_ascii)) {
    /* The SIZE command is _not_ RFC 959 specified, and therefore many servers
       may not support it! It is however the only way we have to get a file's
       size! */

    ftp->transfer = FTPTRANSFER_INFO;
    /* this means no actual transfer will be made */

    /* Some servers return different sizes for different modes, and thus we
       must set the proper type before we check the size */
    result = ftp_nb_type(conn, data->set.prefer_ascii, FTP_TYPE);
    if(result)
      return result;
  }
  else
    result = ftp_state_size(conn);

  return result;
}