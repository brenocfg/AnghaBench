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
struct imap_conn {int /*<<< orphan*/  mailbox_uidvalidity; int /*<<< orphan*/  mailbox; } ;
struct TYPE_4__ {struct imap_conn imapc; } ;
struct connectdata {struct Curl_easy* data; TYPE_2__ proto; } ;
struct IMAP {int /*<<< orphan*/  mailbox; } ;
struct TYPE_3__ {struct IMAP* protop; } ;
struct Curl_easy {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMAP_SELECT ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* imap_atom (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imap_sendf (struct connectdata*,char*,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode imap_perform_select(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct IMAP *imap = data->req.protop;
  struct imap_conn *imapc = &conn->proto.imapc;
  char *mailbox;

  /* Invalidate old information as we are switching mailboxes */
  Curl_safefree(imapc->mailbox);
  Curl_safefree(imapc->mailbox_uidvalidity);

  /* Check we have a mailbox */
  if(!imap->mailbox) {
    failf(conn->data, "Cannot SELECT without a mailbox.");
    return CURLE_URL_MALFORMAT;
  }

  /* Make sure the mailbox is in the correct atom format */
  mailbox = imap_atom(imap->mailbox, false);
  if(!mailbox)
    return CURLE_OUT_OF_MEMORY;

  /* Send the SELECT command */
  result = imap_sendf(conn, "SELECT %s", mailbox);

  free(mailbox);

  if(!result)
    state(conn, IMAP_SELECT);

  return result;
}