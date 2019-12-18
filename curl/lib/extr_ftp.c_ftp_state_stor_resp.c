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
struct ftp_conn {int /*<<< orphan*/  wait_data_conn; int /*<<< orphan*/  state_saved; } ;
struct TYPE_4__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_2__ proto; struct Curl_easy* data; } ;
struct TYPE_3__ {scalar_t__ ftp_use_port; } ;
struct Curl_easy {TYPE_1__ set; } ;
typedef  int /*<<< orphan*/  ftpstate ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  AllowServerConnect (struct connectdata*,int*) ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_UPLOAD_FAILED ; 
 int /*<<< orphan*/  FTP_STOP ; 
 int /*<<< orphan*/  InitiateTransfer (struct connectdata*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_state_stor_resp(struct connectdata *conn,
                                    int ftpcode, ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;

  if(ftpcode >= 400) {
    failf(data, "Failed FTP upload: %0d", ftpcode);
    state(conn, FTP_STOP);
    /* oops, we never close the sockets! */
    return CURLE_UPLOAD_FAILED;
  }

  conn->proto.ftpc.state_saved = instate;

  /* PORT means we are now awaiting the server to connect to us. */
  if(data->set.ftp_use_port) {
    bool connected;

    state(conn, FTP_STOP); /* no longer in STOR state */

    result = AllowServerConnect(conn, &connected);
    if(result)
      return result;

    if(!connected) {
      struct ftp_conn *ftpc = &conn->proto.ftpc;
      infof(data, "Data conn was not available immediately\n");
      ftpc->wait_data_conn = TRUE;
    }

    return CURLE_OK;
  }
  return InitiateTransfer(conn);
}