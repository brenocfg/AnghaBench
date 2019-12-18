#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  context; int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ gdb_stub ;
struct TYPE_7__ {int sock; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ gdb_client ;
typedef  int YabSock ;

/* Variables and functions */
 int /*<<< orphan*/  SH2SetBreakpointCallBack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  YAB_THREAD_GDBSTUBCLIENT ; 
 int YabSockAccept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YabThreadStart (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  gdb_client_lock ; 
 int /*<<< orphan*/  gdb_stub_client ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void gdb_stub_listener(void * data)
{
   gdb_stub * stub = data;
   YabSock sock;

   while(1)
   {
      gdb_client * client;

      sock = YabSockAccept(stub->server);
      if (sock == -1)
      {
         perror("accept");
         return;
      }

      client = malloc(sizeof(gdb_client));
      client->context = stub->context;
      client->sock = sock;

      SH2SetBreakpointCallBack(stub->context, gdb_client_lock, client);

      YabThreadStart(YAB_THREAD_GDBSTUBCLIENT, gdb_stub_client, client);
   }
}