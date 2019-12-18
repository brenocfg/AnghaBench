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
typedef  int /*<<< orphan*/  FDFSStorageBrief ;
typedef  int /*<<< orphan*/  ConnectionInfo ;

/* Variables and functions */
 int /*<<< orphan*/  storage_sync_connect_storage_server_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static inline void storage_sync_connect_storage_server(
        FDFSStorageBrief *pStorage, ConnectionInfo *conn)
{
    bool check_flag = true;
    storage_sync_connect_storage_server_ex(pStorage,
            conn, &check_flag);
}