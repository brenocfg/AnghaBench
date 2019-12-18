#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pingpong {char* sendthis; int /*<<< orphan*/  response; scalar_t__ sendleft; scalar_t__ sendsize; int /*<<< orphan*/  conn; } ;
struct TYPE_8__ {struct pingpong pp; } ;
struct TYPE_9__ {TYPE_2__ smtpc; } ;
struct connectdata {int /*<<< orphan*/  writesockfd; struct Curl_easy* data; TYPE_3__ proto; } ;
struct SMTP {int /*<<< orphan*/  transfer; scalar_t__ trailing_crlf; int /*<<< orphan*/  custom; } ;
struct TYPE_12__ {int /*<<< orphan*/  infilesize; } ;
struct TYPE_10__ {scalar_t__ kind; } ;
struct TYPE_11__ {TYPE_4__ mimepost; scalar_t__ upload; scalar_t__ mail_rcpt; int /*<<< orphan*/  connect_only; } ;
struct TYPE_7__ {struct SMTP* protop; } ;
struct Curl_easy {TYPE_6__ state; TYPE_5__ set; TYPE_1__ req; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_now () ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_write (struct connectdata*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTPTRANSFER_BODY ; 
 int /*<<< orphan*/ * SMTP_EOB ; 
 scalar_t__ SMTP_EOB_LEN ; 
 int /*<<< orphan*/  SMTP_POSTDATA ; 
 int /*<<< orphan*/  connclose (struct connectdata*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ smtp_block_statemach (struct connectdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 
 char* strdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static CURLcode smtp_done(struct connectdata *conn, CURLcode status,
                          bool premature)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct SMTP *smtp = data->req.protop;
  struct pingpong *pp = &conn->proto.smtpc.pp;
  char *eob;
  ssize_t len;
  ssize_t bytes_written;

  (void)premature;

  if(!smtp || !pp->conn)
    return CURLE_OK;

  /* Cleanup our per-request based variables */
  Curl_safefree(smtp->custom);

  if(status) {
    connclose(conn, "SMTP done with bad status"); /* marked for closure */
    result = status;         /* use the already set error code */
  }
  else if(!data->set.connect_only && data->set.mail_rcpt &&
          (data->set.upload || data->set.mimepost.kind)) {
    /* Calculate the EOB taking into account any terminating CRLF from the
       previous line of the email or the CRLF of the DATA command when there
       is "no mail data". RFC-5321, sect. 4.1.1.4.

       Note: As some SSL backends, such as OpenSSL, will cause Curl_write() to
       fail when using a different pointer following a previous write, that
       returned CURLE_AGAIN, we duplicate the EOB now rather than when the
       bytes written doesn't equal len. */
    if(smtp->trailing_crlf || !conn->data->state.infilesize) {
      eob = strdup(&SMTP_EOB[2]);
      len = SMTP_EOB_LEN - 2;
    }
    else {
      eob = strdup(SMTP_EOB);
      len = SMTP_EOB_LEN;
    }

    if(!eob)
      return CURLE_OUT_OF_MEMORY;

    /* Send the end of block data */
    result = Curl_write(conn, conn->writesockfd, eob, len, &bytes_written);
    if(result) {
      free(eob);
      return result;
    }

    if(bytes_written != len) {
      /* The whole chunk was not sent so keep it around and adjust the
         pingpong structure accordingly */
      pp->sendthis = eob;
      pp->sendsize = len;
      pp->sendleft = len - bytes_written;
    }
    else {
      /* Successfully sent so adjust the response timeout relative to now */
      pp->response = Curl_now();

      free(eob);
    }

    state(conn, SMTP_POSTDATA);

    /* Run the state-machine */
    result = smtp_block_statemach(conn, FALSE);
  }

  /* Clear the transfer mode for the next request */
  smtp->transfer = FTPTRANSFER_BODY;

  return result;
}