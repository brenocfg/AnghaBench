#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_3__ {scalar_t__ expire; scalar_t__ access; int /*<<< orphan*/ * taos; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ HttpSession ;

/* Variables and functions */
 int /*<<< orphan*/  httpTrace (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,...) ; 
 scalar_t__ taosGetTimestampSec () ; 

int httpSessionExpired(char *session) {
  HttpSession *pSession = (HttpSession *)session;
  time_t       cur = taosGetTimestampSec();

  if (pSession->taos != NULL) {
    if (pSession->expire > cur) {
      return 0;  // un-expired, so return false
    }
    if (pSession->access > 0) {
      httpTrace("session:%p:%s:%p is expired, but still access:%d", pSession, pSession->id, pSession->taos,
                pSession->access);
      return 0;  // still used, so return false
    }
    httpTrace("need close session:%p:%s:%p for it expired, cur:%d, expire:%d, invertal:%d",
              pSession, pSession->id, pSession->taos, cur, pSession->expire, cur - pSession->expire);
  }

  return 1;
}