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
struct imap_conn {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct imap_conn imapc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  imapstate ;

/* Variables and functions */

__attribute__((used)) static void state(struct connectdata *conn, imapstate newstate)
{
  struct imap_conn *imapc = &conn->proto.imapc;
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  /* for debug purposes */
  static const char * const names[]={
    "STOP",
    "SERVERGREET",
    "CAPABILITY",
    "STARTTLS",
    "UPGRADETLS",
    "AUTHENTICATE",
    "LOGIN",
    "LIST",
    "SELECT",
    "FETCH",
    "FETCH_FINAL",
    "APPEND",
    "APPEND_FINAL",
    "SEARCH",
    "LOGOUT",
    /* LAST */
  };

  if(imapc->state != newstate)
    infof(conn->data, "IMAP %p state change from %s to %s\n",
          (void *)imapc, names[imapc->state], names[newstate]);
#endif

  imapc->state = newstate;
}