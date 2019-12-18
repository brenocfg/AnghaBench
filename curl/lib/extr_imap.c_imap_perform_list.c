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
struct IMAP {char* custom_params; scalar_t__ mailbox; scalar_t__ custom; } ;
struct TYPE_2__ {struct IMAP* protop; } ;
struct Curl_easy {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  IMAP_LIST ; 
 int /*<<< orphan*/  free (char*) ; 
 char* imap_atom (scalar_t__,int) ; 
 int /*<<< orphan*/  imap_sendf (struct connectdata*,char*,char*,...) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 

__attribute__((used)) static CURLcode imap_perform_list(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct IMAP *imap = data->req.protop;

  if(imap->custom)
    /* Send the custom request */
    result = imap_sendf(conn, "%s%s", imap->custom,
                        imap->custom_params ? imap->custom_params : "");
  else {
    /* Make sure the mailbox is in the correct atom format if necessary */
    char *mailbox = imap->mailbox ? imap_atom(imap->mailbox, true)
                                  : strdup("");
    if(!mailbox)
      return CURLE_OUT_OF_MEMORY;

    /* Send the LIST command */
    result = imap_sendf(conn, "LIST \"%s\" *", mailbox);

    free(mailbox);
  }

  if(!result)
    state(conn, IMAP_LIST);

  return result;
}