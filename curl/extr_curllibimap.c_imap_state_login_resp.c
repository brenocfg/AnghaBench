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
typedef  int /*<<< orphan*/  imapstate ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_LOGIN_DENIED ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int IMAP_RESP_OK ; 
 int /*<<< orphan*/  IMAP_STOP ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode imap_state_login_resp(struct connectdata *conn,
                                      int imapcode,
                                      imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;

  (void)instate; /* no use for this yet */

  if(imapcode != IMAP_RESP_OK) {
    failf(data, "Access denied. %c", imapcode);
    result = CURLE_LOGIN_DENIED;
  }
  else
    /* End of connect phase */
    state(conn, IMAP_STOP);

  return result;
}