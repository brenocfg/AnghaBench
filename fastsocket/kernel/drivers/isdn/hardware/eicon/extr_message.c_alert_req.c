#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int byte ;
struct TYPE_5__ {scalar_t__ State; } ;
typedef  TYPE_1__ PLCI ;
typedef  int /*<<< orphan*/  DIVA_CAPI_ADAPTER ;
typedef  int /*<<< orphan*/  APPL ;
typedef  int /*<<< orphan*/  API_PARSE ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_ALERT ; 
 int CONFIRM ; 
 scalar_t__ INC_CON_ALERT ; 
 scalar_t__ INC_CON_PENDING ; 
 scalar_t__ _ALERT_IGNORED ; 
 int _ALERT_R ; 
 scalar_t__ _WRONG_IDENTIFIER ; 
 scalar_t__ _WRONG_STATE ; 
 int /*<<< orphan*/  add_ai (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  sendf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  sig_req (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static byte alert_req(dword Id, word Number, DIVA_CAPI_ADAPTER *a,
		      PLCI *plci, APPL *appl, API_PARSE *msg)
{
  word Info;
  byte ret;

  dbug(1,dprintf("alert_req"));

  Info = _WRONG_IDENTIFIER;
  ret = false;
  if(plci) {
    Info = _ALERT_IGNORED;
    if(plci->State!=INC_CON_ALERT) {
      Info = _WRONG_STATE;
      if(plci->State==INC_CON_PENDING) {
        Info = 0;
        plci->State=INC_CON_ALERT;
        add_ai(plci, &msg[0]);
        sig_req(plci,CALL_ALERT,0);
        ret = 1;
      }
    }
  }
  sendf(appl,
        _ALERT_R|CONFIRM,
        Id,
        Number,
        "w",Info);
  return ret;
}