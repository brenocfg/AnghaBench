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
struct TYPE_3__ {int /*<<< orphan*/  link; } ;
typedef  TYPE_1__ StorageBinLogReader ;

/* Variables and functions */
 int /*<<< orphan*/  fc_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_head ; 
 int /*<<< orphan*/  sync_thread_lock ; 

void storage_reader_add_to_list(StorageBinLogReader *pReader)
{
	pthread_mutex_lock(&sync_thread_lock);
    fc_list_add_tail(&pReader->link, &reader_head);
	pthread_mutex_unlock(&sync_thread_lock);
}