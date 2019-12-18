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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  gdb_client ;

/* Variables and functions */
 int /*<<< orphan*/  YAB_THREAD_GDBSTUBCLIENT ; 
 int /*<<< orphan*/  YabThreadRemoteSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_client_send (int /*<<< orphan*/ *,char*,int) ; 

void gdb_client_lock(void *context, u32 addr, void * userdata) {
   gdb_client * client = userdata;

   gdb_client_send(client, "S05", 3);

   YabThreadRemoteSleep(YAB_THREAD_GDBSTUBCLIENT);
}