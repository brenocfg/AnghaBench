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
struct TELNET {int* us; int* us_preferred; int* subnegotiation; int* usq; int* himq; } ;
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
 int /*<<< orphan*/  sendsuboption (struct connectdata*,int) ; 

__attribute__((used)) static
void rec_do(struct connectdata *conn, int option)
{
  struct TELNET *tn = (struct TELNET *)conn->data->req.protop;
  switch(tn->us[option]) {
  case CURL_NO:
    if(tn->us_preferred[option] == CURL_YES) {
      tn->us[option] = CURL_YES;
      send_negotiation(conn, CURL_WILL, option);
      if(tn->subnegotiation[option] == CURL_YES)
        /* transmission of data option */
        sendsuboption(conn, option);
    }
    else if(tn->subnegotiation[option] == CURL_YES) {
      /* send information to achieve this option*/
      tn->us[option] = CURL_YES;
      send_negotiation(conn, CURL_WILL, option);
      sendsuboption(conn, option);
    }
    else
      send_negotiation(conn, CURL_WONT, option);
    break;

  case CURL_YES:
    /* Already enabled */
    break;

  case CURL_WANTNO:
    switch(tn->usq[option]) {
    case CURL_EMPTY:
      /* Error: DONT answered by WILL */
      tn->us[option] = CURL_NO;
      break;
    case CURL_OPPOSITE:
      /* Error: DONT answered by WILL */
      tn->us[option] = CURL_YES;
      tn->usq[option] = CURL_EMPTY;
      break;
    }
    break;

  case CURL_WANTYES:
    switch(tn->usq[option]) {
    case CURL_EMPTY:
      tn->us[option] = CURL_YES;
      if(tn->subnegotiation[option] == CURL_YES) {
        /* transmission of data option */
        sendsuboption(conn, option);
      }
      break;
    case CURL_OPPOSITE:
      tn->us[option] = CURL_WANTNO;
      tn->himq[option] = CURL_EMPTY;
      send_negotiation(conn, CURL_WONT, option);
      break;
    }
    break;
  }
}