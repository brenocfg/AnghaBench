#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connectdata {int /*<<< orphan*/ * sock; } ;

/* Variables and functions */
 int CURL_CSELECT_ERR ; 
 int CURL_CSELECT_IN ; 
 int /*<<< orphan*/  Curl_connalive (struct connectdata*) ; 
 int FALSE ; 
 size_t FIRSTSOCKET ; 
 int SOCKET_READABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 

__attribute__((used)) static bool rtsp_connisdead(struct connectdata *check)
{
  int sval;
  bool ret_val = TRUE;

  sval = SOCKET_READABLE(check->sock[FIRSTSOCKET], 0);
  if(sval == 0) {
    /* timeout */
    ret_val = FALSE;
  }
  else if(sval & CURL_CSELECT_ERR) {
    /* socket is in an error state */
    ret_val = TRUE;
  }
  else if(sval & CURL_CSELECT_IN) {
    /* readable with no error. could still be closed */
    ret_val = !Curl_connalive(check);
  }

  return ret_val;
}