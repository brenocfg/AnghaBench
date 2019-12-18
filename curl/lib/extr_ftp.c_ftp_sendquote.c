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
struct pingpong {int /*<<< orphan*/  response; } ;
struct ftp_conn {struct pingpong pp; } ;
struct curl_slist {char* data; struct curl_slist* next; } ;
struct TYPE_2__ {struct ftp_conn ftpc; } ;
struct connectdata {int /*<<< orphan*/  data; TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_QUOTE_ERROR ; 
 scalar_t__ Curl_GetFTPResponse (int /*<<< orphan*/ *,struct connectdata*,int*) ; 
 int /*<<< orphan*/  Curl_now () ; 
 int FALSE ; 
 int /*<<< orphan*/  PPSENDF (struct pingpong*,char*,char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  failf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static
CURLcode ftp_sendquote(struct connectdata *conn, struct curl_slist *quote)
{
  struct curl_slist *item;
  ssize_t nread;
  int ftpcode;
  CURLcode result;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  struct pingpong *pp = &ftpc->pp;

  item = quote;
  while(item) {
    if(item->data) {
      char *cmd = item->data;
      bool acceptfail = FALSE;

      /* if a command starts with an asterisk, which a legal FTP command never
         can, the command will be allowed to fail without it causing any
         aborts or cancels etc. It will cause libcurl to act as if the command
         is successful, whatever the server reponds. */

      if(cmd[0] == '*') {
        cmd++;
        acceptfail = TRUE;
      }

      PPSENDF(&conn->proto.ftpc.pp, "%s", cmd);

      pp->response = Curl_now(); /* timeout relative now */

      result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
      if(result)
        return result;

      if(!acceptfail && (ftpcode >= 400)) {
        failf(conn->data, "QUOT string not accepted: %s", cmd);
        return CURLE_QUOTE_ERROR;
      }
    }

    item = item->next;
  }

  return CURLE_OK;
}