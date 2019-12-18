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
struct ftp_conn {scalar_t__ state; int /*<<< orphan*/  pp; } ;
struct TYPE_6__ {struct ftp_conn ftpc; } ;
struct connectdata {struct Curl_easy* data; TYPE_2__ proto; } ;
struct FTP {char* passwd; } ;
struct TYPE_8__ {scalar_t__ ftp_trying_alternative; } ;
struct TYPE_7__ {char** str; } ;
struct TYPE_5__ {struct FTP* protop; } ;
struct Curl_easy {TYPE_4__ state; TYPE_3__ set; TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  ftpstate ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_LOGIN_DENIED ; 
 int /*<<< orphan*/  CURLE_OK ; 
 scalar_t__ FTP_ACCT ; 
 scalar_t__ FTP_PASS ; 
 scalar_t__ FTP_USER ; 
 int /*<<< orphan*/  PPSENDF (int /*<<< orphan*/ *,char*,char*) ; 
 size_t STRING_FTP_ACCOUNT ; 
 size_t STRING_FTP_ALTERNATIVE_TO_USER ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 int /*<<< orphan*/  ftp_state_loggedin (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,scalar_t__) ; 

__attribute__((used)) static CURLcode ftp_state_user_resp(struct connectdata *conn,
                                    int ftpcode,
                                    ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct FTP *ftp = data->req.protop;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  (void)instate; /* no use for this yet */

  /* some need password anyway, and others just return 2xx ignored */
  if((ftpcode == 331) && (ftpc->state == FTP_USER)) {
    /* 331 Password required for ...
       (the server requires to send the user's password too) */
    PPSENDF(&ftpc->pp, "PASS %s", ftp->passwd?ftp->passwd:"");
    state(conn, FTP_PASS);
  }
  else if(ftpcode/100 == 2) {
    /* 230 User ... logged in.
       (the user logged in with or without password) */
    result = ftp_state_loggedin(conn);
  }
  else if(ftpcode == 332) {
    if(data->set.str[STRING_FTP_ACCOUNT]) {
      PPSENDF(&ftpc->pp, "ACCT %s", data->set.str[STRING_FTP_ACCOUNT]);
      state(conn, FTP_ACCT);
    }
    else {
      failf(data, "ACCT requested but none available");
      result = CURLE_LOGIN_DENIED;
    }
  }
  else {
    /* All other response codes, like:

    530 User ... access denied
    (the server denies to log the specified user) */

    if(conn->data->set.str[STRING_FTP_ALTERNATIVE_TO_USER] &&
        !conn->data->state.ftp_trying_alternative) {
      /* Ok, USER failed.  Let's try the supplied command. */
      PPSENDF(&conn->proto.ftpc.pp, "%s",
              conn->data->set.str[STRING_FTP_ALTERNATIVE_TO_USER]);
      conn->data->state.ftp_trying_alternative = TRUE;
      state(conn, FTP_USER);
      result = CURLE_OK;
    }
    else {
      failf(data, "Access denied: %03d", ftpcode);
      result = CURLE_LOGIN_DENIED;
    }
  }
  return result;
}