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
struct storage_nio_thread_data {int /*<<< orphan*/  thread_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
struct fast_task_info {TYPE_1__ event; scalar_t__ arg; } ;
struct TYPE_4__ {int nio_thread_index; int /*<<< orphan*/  stage; } ;
typedef  TYPE_2__ StorageClientInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FDFS_STORAGE_STAGE_NIO_RECV ; 
 int /*<<< orphan*/  IOEVENT_READ ; 
 int /*<<< orphan*/  client_sock_read ; 
 int /*<<< orphan*/  g_fdfs_network_timeout ; 
 struct storage_nio_thread_data* g_nio_thread_data ; 
 int ioevent_set (struct fast_task_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int storage_nio_init(struct fast_task_info *pTask)
{
	StorageClientInfo *pClientInfo;
	struct storage_nio_thread_data *pThreadData;

	pClientInfo = (StorageClientInfo *)pTask->arg;
	pThreadData = g_nio_thread_data + pClientInfo->nio_thread_index;

	pClientInfo->stage = FDFS_STORAGE_STAGE_NIO_RECV;
	return ioevent_set(pTask, &pThreadData->thread_data,
			pTask->event.fd, IOEVENT_READ, client_sock_read,
			g_fdfs_network_timeout);
}