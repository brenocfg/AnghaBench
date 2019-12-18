#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  serverMutex; int /*<<< orphan*/  processData; int /*<<< orphan*/  numOfThreads; int /*<<< orphan*/  sessionExpire; int /*<<< orphan*/  cacheContext; int /*<<< orphan*/  serverPort; int /*<<< orphan*/  serverIp; int /*<<< orphan*/  label; } ;
typedef  TYPE_1__ HttpServer ;

/* Variables and functions */
 int /*<<< orphan*/  adminInitHandle (TYPE_1__*) ; 
 int /*<<< orphan*/  gcInitHandle (TYPE_1__*) ; 
 int /*<<< orphan*/  httpProcessData ; 
 TYPE_1__* httpServer ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opInitHandle (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restInitHandle (TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taosInitNote (int,int) ; 
 int /*<<< orphan*/  taos_init () ; 
 int /*<<< orphan*/  tgInitHandle (TYPE_1__*) ; 
 int /*<<< orphan*/  tsHttpCacheSessions ; 
 scalar_t__ tsHttpEnableRecordSql ; 
 char* tsHttpIp ; 
 int /*<<< orphan*/  tsHttpMaxThreads ; 
 int /*<<< orphan*/  tsHttpPort ; 
 int /*<<< orphan*/  tsHttpSessionExpire ; 
 int tsNumOfLogLines ; 

int httpInitSystem() {
  taos_init();

  httpServer = (HttpServer *)malloc(sizeof(HttpServer));
  memset(httpServer, 0, sizeof(HttpServer));

  strcpy(httpServer->label, "rest");
  strcpy(httpServer->serverIp, tsHttpIp);
  httpServer->serverPort = tsHttpPort;
  httpServer->cacheContext = tsHttpCacheSessions;
  httpServer->sessionExpire = tsHttpSessionExpire;
  httpServer->numOfThreads = tsHttpMaxThreads;
  httpServer->processData = httpProcessData;

  pthread_mutex_init(&httpServer->serverMutex, NULL);

  if (tsHttpEnableRecordSql != 0) {
    taosInitNote(tsNumOfLogLines / 10, 1);
  }
  restInitHandle(httpServer);
  adminInitHandle(httpServer);
  gcInitHandle(httpServer);
  tgInitHandle(httpServer);
  opInitHandle(httpServer);

  return 0;
}