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
struct ftp_conn {int /*<<< orphan*/  file; int /*<<< orphan*/  pp; } ;
struct TYPE_2__ {struct ftp_conn ftpc; } ;
struct connectdata {int /*<<< orphan*/  data; TYPE_1__ proto; } ;
typedef  int ftpstate ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_FTP_COULDNT_USE_REST ; 
 int /*<<< orphan*/  CURLE_OK ; 
#define  FTP_REST 129 
 int /*<<< orphan*/  FTP_RETR ; 
#define  FTP_RETR_REST 128 
 int /*<<< orphan*/  PPSENDF (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ftp_state_prepare_transfer (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_state_rest_resp(struct connectdata *conn,
                                    int ftpcode,
                                    ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  switch(instate) {
  case FTP_REST:
  default:
#ifdef CURL_FTP_HTTPSTYLE_HEAD
    if(ftpcode == 350) {
      char buffer[24]= { "Accept-ranges: bytes\r\n" };
      result = Curl_client_write(conn, CLIENTWRITE_BOTH, buffer, 0);
      if(result)
        return result;
    }
#endif
    result = ftp_state_prepare_transfer(conn);
    break;

  case FTP_RETR_REST:
    if(ftpcode != 350) {
      failf(conn->data, "Couldn't use REST");
      result = CURLE_FTP_COULDNT_USE_REST;
    }
    else {
      PPSENDF(&ftpc->pp, "RETR %s", ftpc->file);
      state(conn, FTP_RETR);
    }
    break;
  }

  return result;
}