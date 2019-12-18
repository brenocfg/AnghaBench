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
struct connectdata {TYPE_2__* data; } ;
struct IMAP {char* section; scalar_t__ mindex; scalar_t__ partial; scalar_t__ uid; } ;
struct TYPE_3__ {struct IMAP* protop; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  IMAP_FETCH ; 
 int /*<<< orphan*/  failf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  imap_sendf (struct connectdata*,char*,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode imap_perform_fetch(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct IMAP *imap = conn->data->req.protop;
  /* Check we have a UID */
  if(imap->uid) {

    /* Send the FETCH command */
    if(imap->partial)
      result = imap_sendf(conn, "UID FETCH %s BODY[%s]<%s>",
                            imap->uid,
                            imap->section ? imap->section : "",
                            imap->partial);
    else
      result = imap_sendf(conn, "UID FETCH %s BODY[%s]",
                            imap->uid,
                            imap->section ? imap->section : "");
  }
  else if(imap->mindex) {

    /* Send the FETCH command */
    if(imap->partial)
      result = imap_sendf(conn, "FETCH %s BODY[%s]<%s>",
                            imap->mindex,
                            imap->section ? imap->section : "",
                            imap->partial);
    else
      result = imap_sendf(conn, "FETCH %s BODY[%s]",
                            imap->mindex,
                            imap->section ? imap->section : "");
  }
  else {
        failf(conn->data, "Cannot FETCH without a UID.");
        return CURLE_URL_MALFORMAT;
  }
  if(!result)
    state(conn, IMAP_FETCH);

  return result;
}