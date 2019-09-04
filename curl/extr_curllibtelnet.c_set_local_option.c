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
struct TELNET {int* us; int* usq; } ;
struct TYPE_3__ {scalar_t__ protop; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
#define  CURL_EMPTY 133 
#define  CURL_NO 132 
#define  CURL_OPPOSITE 131 
#define  CURL_WANTNO 130 
#define  CURL_WANTYES 129 
 int /*<<< orphan*/  CURL_WILL ; 
 int /*<<< orphan*/  CURL_WONT ; 
#define  CURL_YES 128 
 int /*<<< orphan*/  send_negotiation (struct connectdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_local_option(struct connectdata *conn, int option, int newstate)
{
  struct TELNET *tn = (struct TELNET *)conn->data->req.protop;
  if(newstate == CURL_YES) {
    switch(tn->us[option]) {
    case CURL_NO:
      tn->us[option] = CURL_WANTYES;
      send_negotiation(conn, CURL_WILL, option);
      break;

    case CURL_YES:
      /* Already enabled */
      break;

    case CURL_WANTNO:
      switch(tn->usq[option]) {
      case CURL_EMPTY:
        /* Already negotiating for CURL_YES, queue the request */
        tn->usq[option] = CURL_OPPOSITE;
        break;
      case CURL_OPPOSITE:
        /* Error: already queued an enable request */
        break;
      }
      break;

    case CURL_WANTYES:
      switch(tn->usq[option]) {
      case CURL_EMPTY:
        /* Error: already negotiating for enable */
        break;
      case CURL_OPPOSITE:
        tn->usq[option] = CURL_EMPTY;
        break;
      }
      break;
    }
  }
  else { /* NO */
    switch(tn->us[option]) {
    case CURL_NO:
      /* Already disabled */
      break;

    case CURL_YES:
      tn->us[option] = CURL_WANTNO;
      send_negotiation(conn, CURL_WONT, option);
      break;

    case CURL_WANTNO:
      switch(tn->usq[option]) {
      case CURL_EMPTY:
        /* Already negotiating for NO */
        break;
      case CURL_OPPOSITE:
        tn->usq[option] = CURL_EMPTY;
        break;
      }
      break;

    case CURL_WANTYES:
      switch(tn->usq[option]) {
      case CURL_EMPTY:
        tn->usq[option] = CURL_OPPOSITE;
        break;
      case CURL_OPPOSITE:
        break;
      }
      break;
    }
  }
}