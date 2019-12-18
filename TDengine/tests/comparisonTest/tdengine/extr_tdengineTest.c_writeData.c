#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int threadId; int sID; int eID; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ ThreadObj ;
struct TYPE_8__ {int writeClients; char* dataDir; int filesNum; int rowsPerRequest; } ;
struct TYPE_7__ {scalar_t__ totalRows; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 TYPE_5__ arguments ; 
 TYPE_1__* calloc (size_t,int) ; 
 scalar_t__ getTimeStampMs () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ statis ; 
 void* taos_connect (char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taos_error (void*) ; 
 int /*<<< orphan*/  taos_init () ; 
 int taos_query (void*,char*) ; 
 scalar_t__ writeDataImp ; 

void writeData() {
  printf("write data\n");
  printf("---- writeClients: %d\n", arguments.writeClients);
  printf("---- dataDir: %s\n", arguments.dataDir);
  printf("---- numOfFiles: %d\n", arguments.filesNum);
  printf("---- rowsPerRequest: %d\n", arguments.rowsPerRequest);

  taos_init();

  void *taos = taos_connect("127.0.0.1", "root", "taosdata", NULL, 0);
  if (taos == NULL)
    taos_error(taos);

  int code = taos_query(taos, "create database if not exists db");
  if (code != 0) {
    taos_error(taos);
  }

  code = taos_query(taos, "create table if not exists db.devices(ts timestamp, temperature int, humidity float) "
    "tags(devid int, devname binary(16), devgroup int)");
  if (code != 0) {
    taos_error(taos);
  }

  int64_t st = getTimeStampMs();

  int a = arguments.filesNum / arguments.writeClients;
  int b = arguments.filesNum % arguments.writeClients;
  int last = 0;

  ThreadObj *threads = calloc((size_t)arguments.writeClients, sizeof(ThreadObj));
  for (int i = 0; i < arguments.writeClients; ++i) {
    ThreadObj *pthread = threads + i;
    pthread_attr_t thattr;
    pthread->threadId = i + 1;
    pthread->sID = last;
    if (i < b) {
      pthread->eID = last + a;
    } else {
      pthread->eID = last + a - 1;
    }
    last = pthread->eID + 1;
    pthread_attr_init(&thattr);
    pthread_attr_setdetachstate(&thattr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&pthread->pid, &thattr, (void *(*)(void *))writeDataImp, pthread);
  }

  for (int i = 0; i < arguments.writeClients; i++) {
    pthread_join(threads[i].pid, NULL);
  }

  int64_t elapsed = getTimeStampMs() - st;
  float seconds = (float)elapsed / 1000;
  float rs = (float)statis.totalRows / seconds;

  printf("---- Spent %f seconds to insert %ld records, speed: %f Rows/Second\n", seconds, statis.totalRows, rs);
}