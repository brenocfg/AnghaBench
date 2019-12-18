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
struct pingpong {struct connectdata* conn; } ;
struct connectdata {struct Curl_easy* data; } ;
struct TYPE_4__ {int httpcode; } ;
struct TYPE_3__ {char* buffer; } ;
struct Curl_easy {TYPE_2__ info; TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OPERATION_TIMEDOUT ; 
 int /*<<< orphan*/  Curl_pp_readresp (int /*<<< orphan*/ ,struct pingpong*,int*,size_t*) ; 
 int Curl_sec_read_msg (struct connectdata*,char* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTP_STOP ; 
 int /*<<< orphan*/  PROT_CONFIDENTIAL ; 
 int /*<<< orphan*/  PROT_PRIVATE ; 
 int /*<<< orphan*/  PROT_SAFE ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_readresp(curl_socket_t sockfd,
                             struct pingpong *pp,
                             int *ftpcode, /* return the ftp-code if done */
                             size_t *size) /* size of the response */
{
  struct connectdata *conn = pp->conn;
  struct Curl_easy *data = conn->data;
#ifdef HAVE_GSSAPI
  char * const buf = data->state.buffer;
#endif
  int code;
  CURLcode result = Curl_pp_readresp(sockfd, pp, &code, size);

#if defined(HAVE_GSSAPI)
  /* handle the security-oriented responses 6xx ***/
  switch(code) {
  case 631:
    code = Curl_sec_read_msg(conn, buf, PROT_SAFE);
    break;
  case 632:
    code = Curl_sec_read_msg(conn, buf, PROT_PRIVATE);
    break;
  case 633:
    code = Curl_sec_read_msg(conn, buf, PROT_CONFIDENTIAL);
    break;
  default:
    /* normal ftp stuff we pass through! */
    break;
  }
#endif

  /* store the latest code for later retrieval */
  data->info.httpcode = code;

  if(ftpcode)
    *ftpcode = code;

  if(421 == code) {
    /* 421 means "Service not available, closing control connection." and FTP
     * servers use it to signal that idle session timeout has been exceeded.
     * If we ignored the response, it could end up hanging in some cases.
     *
     * This response code can come at any point so having it treated
     * generically is a good idea.
     */
    infof(data, "We got a 421 - timeout!\n");
    state(conn, FTP_STOP);
    return CURLE_OPERATION_TIMEDOUT;
  }

  return result;
}