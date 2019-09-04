#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connectdata {struct Curl_easy* data; } ;
struct Curl_easy {int dummy; } ;
typedef  scalar_t__ ftpstate ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_FTP_COULDNT_SET_TYPE ; 
 int /*<<< orphan*/  CURLE_OK ; 
 scalar_t__ FTP_LIST_TYPE ; 
 scalar_t__ FTP_RETR_TYPE ; 
 scalar_t__ FTP_STOR_TYPE ; 
 scalar_t__ FTP_TYPE ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  ftp_state_list (struct connectdata*) ; 
 int /*<<< orphan*/  ftp_state_retr_prequote (struct connectdata*) ; 
 int /*<<< orphan*/  ftp_state_size (struct connectdata*) ; 
 int /*<<< orphan*/  ftp_state_stor_prequote (struct connectdata*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int) ; 

__attribute__((used)) static CURLcode ftp_state_type_resp(struct connectdata *conn,
                                    int ftpcode,
                                    ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;

  if(ftpcode/100 != 2) {
    /* "sasserftpd" and "(u)r(x)bot ftpd" both responds with 226 after a
       successful 'TYPE I'. While that is not as RFC959 says, it is still a
       positive response code and we allow that. */
    failf(data, "Couldn't set desired mode");
    return CURLE_FTP_COULDNT_SET_TYPE;
  }
  if(ftpcode != 200)
    infof(data, "Got a %03d response code instead of the assumed 200\n",
          ftpcode);

  if(instate == FTP_TYPE)
    result = ftp_state_size(conn);
  else if(instate == FTP_LIST_TYPE)
    result = ftp_state_list(conn);
  else if(instate == FTP_RETR_TYPE)
    result = ftp_state_retr_prequote(conn);
  else if(instate == FTP_STOR_TYPE)
    result = ftp_state_stor_prequote(conn);

  return result;
}