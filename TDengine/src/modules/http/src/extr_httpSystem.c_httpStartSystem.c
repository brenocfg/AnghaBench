#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * timerHandle; int /*<<< orphan*/ * pContextPool; int /*<<< orphan*/  cacheContext; } ;
typedef  int /*<<< orphan*/  HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  httpError (char*) ; 
 int /*<<< orphan*/  httpInitAllSessions (TYPE_1__*) ; 
 int /*<<< orphan*/  httpInitConnect (TYPE_1__*) ; 
 int /*<<< orphan*/  httpInitSystem () ; 
 int /*<<< orphan*/  httpPrint (char*) ; 
 TYPE_1__* httpServer ; 
 int /*<<< orphan*/ * taosMemPoolInit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * taosTmrInit (int,int,int,char*) ; 
 int tsHttpCacheSessions ; 

int httpStartSystem() {
  httpPrint("starting to initialize http service ...");

  if (httpServer == NULL) {
    httpError("http server is null");
    httpInitSystem();
  }

  if (httpServer->pContextPool == NULL) {
    httpServer->pContextPool = taosMemPoolInit(httpServer->cacheContext, sizeof(HttpContext));
  }
  if (httpServer->pContextPool == NULL) {
    httpError("http init context pool failed");
    return -1;
  }

  if (httpServer->timerHandle == NULL) {
    httpServer->timerHandle = taosTmrInit(tsHttpCacheSessions * 20 + 100, 1000, 60000, "http");
  }
  if (httpServer->timerHandle == NULL) {
    httpError("http init timer failed");
    return -1;
  }

  if (!httpInitAllSessions(httpServer)) {
    httpError("http init session failed");
    return -1;
  }

  if (!httpInitConnect(httpServer)) {
    httpError("http init server failed");
    return -1;
  }

  return 0;
}