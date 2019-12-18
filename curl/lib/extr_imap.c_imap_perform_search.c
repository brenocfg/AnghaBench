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
struct IMAP {int /*<<< orphan*/  query; } ;
struct TYPE_3__ {struct IMAP* protop; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  IMAP_SEARCH ; 
 int /*<<< orphan*/  failf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  imap_sendf (struct connectdata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode imap_perform_search(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct IMAP *imap = conn->data->req.protop;

  /* Check we have a query string */
  if(!imap->query) {
    failf(conn->data, "Cannot SEARCH without a query string.");
    return CURLE_URL_MALFORMAT;
  }

  /* Send the SEARCH command */
  result = imap_sendf(conn, "SEARCH %s", imap->query);

  if(!result)
    state(conn, IMAP_SEARCH);

  return result;
}