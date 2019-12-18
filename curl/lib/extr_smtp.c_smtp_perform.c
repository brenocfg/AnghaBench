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
struct TYPE_8__ {int* tcpconnect; } ;
struct connectdata {struct Curl_easy* data; TYPE_4__ bits; } ;
struct SMTP {int eob; int /*<<< orphan*/  trailing_crlf; scalar_t__ rcpt; int /*<<< orphan*/  transfer; } ;
struct TYPE_6__ {scalar_t__ kind; } ;
struct TYPE_7__ {scalar_t__ mail_rcpt; TYPE_2__ mimepost; scalar_t__ upload; scalar_t__ opt_no_body; } ;
struct TYPE_5__ {struct SMTP* protop; } ;
struct Curl_easy {TYPE_3__ set; TYPE_1__ req; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 size_t FIRSTSOCKET ; 
 int /*<<< orphan*/  FTPTRANSFER_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 scalar_t__ smtp_multi_statemach (struct connectdata*,int*) ; 
 scalar_t__ smtp_perform_command (struct connectdata*) ; 
 scalar_t__ smtp_perform_mail (struct connectdata*) ; 

__attribute__((used)) static CURLcode smtp_perform(struct connectdata *conn, bool *connected,
                             bool *dophase_done)
{
  /* This is SMTP and no proxy */
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct SMTP *smtp = data->req.protop;

  DEBUGF(infof(conn->data, "DO phase starts\n"));

  if(data->set.opt_no_body) {
    /* Requested no body means no transfer */
    smtp->transfer = FTPTRANSFER_INFO;
  }

  *dophase_done = FALSE; /* not done yet */

  /* Store the first recipient (or NULL if not specified) */
  smtp->rcpt = data->set.mail_rcpt;

  /* Initial data character is the first character in line: it is implicitly
     preceded by a virtual CRLF. */
  smtp->trailing_crlf = TRUE;
  smtp->eob = 2;

  /* Start the first command in the DO phase */
  if((data->set.upload || data->set.mimepost.kind) && data->set.mail_rcpt)
    /* MAIL transfer */
    result = smtp_perform_mail(conn);
  else
    /* SMTP based command (VRFY, EXPN, NOOP, RSET or HELP) */
    result = smtp_perform_command(conn);

  if(result)
    return result;

  /* Run the state-machine */
  result = smtp_multi_statemach(conn, dophase_done);

  *connected = conn->bits.tcpconnect[FIRSTSOCKET];

  if(*dophase_done)
    DEBUGF(infof(conn->data, "DO phase is complete\n"));

  return result;
}