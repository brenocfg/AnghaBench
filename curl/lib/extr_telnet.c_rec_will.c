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
struct TELNET {int* him; int* him_preferred; int* himq; } ;
struct TYPE_3__ {scalar_t__ protop; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_DO ; 
 int /*<<< orphan*/  CURL_DONT ; 
#define  CURL_EMPTY 133 
#define  CURL_NO 132 
#define  CURL_OPPOSITE 131 
#define  CURL_WANTNO 130 
#define  CURL_WANTYES 129 
#define  CURL_YES 128 
 int /*<<< orphan*/  send_negotiation (struct connectdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
void rec_will(struct connectdata *conn, int option)
{
  struct TELNET *tn = (struct TELNET *)conn->data->req.protop;
  switch(tn->him[option]) {
  case CURL_NO:
    if(tn->him_preferred[option] == CURL_YES) {
      tn->him[option] = CURL_YES;
      send_negotiation(conn, CURL_DO, option);
    }
    else
      send_negotiation(conn, CURL_DONT, option);

    break;

  case CURL_YES:
    /* Already enabled */
    break;

  case CURL_WANTNO:
    switch(tn->himq[option]) {
    case CURL_EMPTY:
      /* Error: DONT answered by WILL */
      tn->him[option] = CURL_NO;
      break;
    case CURL_OPPOSITE:
      /* Error: DONT answered by WILL */
      tn->him[option] = CURL_YES;
      tn->himq[option] = CURL_EMPTY;
      break;
    }
    break;

  case CURL_WANTYES:
    switch(tn->himq[option]) {
    case CURL_EMPTY:
      tn->him[option] = CURL_YES;
      break;
    case CURL_OPPOSITE:
      tn->him[option] = CURL_WANTNO;
      tn->himq[option] = CURL_EMPTY;
      send_negotiation(conn, CURL_DONT, option);
      break;
    }
    break;
  }
}