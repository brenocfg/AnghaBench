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
struct TYPE_6__ {int /*<<< orphan*/  pp; } ;
struct TYPE_7__ {TYPE_2__ smtpc; } ;
struct connectdata {TYPE_3__ proto; struct Curl_easy* data; } ;
struct SMTP {TYPE_1__* rcpt; } ;
struct TYPE_8__ {struct SMTP* protop; } ;
struct Curl_easy {TYPE_4__ req; } ;
typedef  int /*<<< orphan*/  smtpstate ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_SEND_ERROR ; 
 int /*<<< orphan*/  Curl_pp_sendf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  SMTP_DATA ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int) ; 
 int /*<<< orphan*/  smtp_perform_rcpt_to (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode smtp_state_rcpt_resp(struct connectdata *conn, int smtpcode,
                                     smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct SMTP *smtp = data->req.protop;

  (void)instate; /* no use for this yet */

  if(smtpcode/100 != 2) {
    failf(data, "RCPT failed: %d", smtpcode);
    result = CURLE_SEND_ERROR;
  }
  else {
    smtp->rcpt = smtp->rcpt->next;

    if(smtp->rcpt)
      /* Send the next RCPT TO command */
      result = smtp_perform_rcpt_to(conn);
    else {
      /* Send the DATA command */
      result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s", "DATA");

      if(!result)
        state(conn, SMTP_DATA);
    }
  }

  return result;
}