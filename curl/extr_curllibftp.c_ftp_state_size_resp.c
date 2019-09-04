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
struct connectdata {struct Curl_easy* data; } ;
struct TYPE_2__ {char* buffer; int resume_from; } ;
struct Curl_easy {TYPE_1__ state; } ;
typedef  scalar_t__ ftpstate ;
typedef  int curl_off_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_pgrsSetDownloadSize (struct Curl_easy*,int) ; 
 scalar_t__ FTP_RETR_SIZE ; 
 scalar_t__ FTP_SIZE ; 
 scalar_t__ FTP_STOR_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curlx_strtoofft (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ftp_state_rest (struct connectdata*) ; 
 int /*<<< orphan*/  ftp_state_retr (struct connectdata*,int) ; 
 int /*<<< orphan*/  ftp_state_ul_setup (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_state_size_resp(struct connectdata *conn,
                                    int ftpcode,
                                    ftpstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  curl_off_t filesize = -1;
  char *buf = data->state.buffer;

  /* get the size from the ascii string: */
  if(ftpcode == 213)
    /* ignores parsing errors, which will make the size remain unknown */
    (void)curlx_strtoofft(buf + 4, NULL, 0, &filesize);

  if(instate == FTP_SIZE) {
#ifdef CURL_FTP_HTTPSTYLE_HEAD
    if(-1 != filesize) {
      char clbuf[128];
      msnprintf(clbuf, sizeof(clbuf),
                "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", filesize);
      result = Curl_client_write(conn, CLIENTWRITE_BOTH, clbuf, 0);
      if(result)
        return result;
    }
#endif
    Curl_pgrsSetDownloadSize(data, filesize);
    result = ftp_state_rest(conn);
  }
  else if(instate == FTP_RETR_SIZE) {
    Curl_pgrsSetDownloadSize(data, filesize);
    result = ftp_state_retr(conn, filesize);
  }
  else if(instate == FTP_STOR_SIZE) {
    data->state.resume_from = filesize;
    result = ftp_state_ul_setup(conn, TRUE);
  }

  return result;
}