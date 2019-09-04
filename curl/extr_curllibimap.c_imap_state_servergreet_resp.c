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
struct imap_conn {int /*<<< orphan*/  preauth; } ;
struct TYPE_2__ {struct imap_conn imapc; } ;
struct connectdata {TYPE_1__ proto; struct Curl_easy* data; } ;
struct Curl_easy {int dummy; } ;
typedef  int /*<<< orphan*/  imapstate ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_WEIRD_SERVER_REPLY ; 
 int IMAP_RESP_OK ; 
 int IMAP_RESP_PREAUTH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  imap_perform_capability (struct connectdata*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 

__attribute__((used)) static CURLcode imap_state_servergreet_resp(struct connectdata *conn,
                                            int imapcode,
                                            imapstate instate)
{
  struct Curl_easy *data = conn->data;
  (void)instate; /* no use for this yet */

  if(imapcode == IMAP_RESP_PREAUTH) {
    /* PREAUTH */
    struct imap_conn *imapc = &conn->proto.imapc;
    imapc->preauth = TRUE;
    infof(data, "PREAUTH connection, already authenticated!\n");
  }
  else if(imapcode != IMAP_RESP_OK) {
    failf(data, "Got unexpected imap-server response");
    return CURLE_WEIRD_SERVER_REPLY;
  }

  return imap_perform_capability(conn);
}