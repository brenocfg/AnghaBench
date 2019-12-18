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
struct r3964_info {struct r3964_client_info* firstClient; } ;
struct r3964_client_info {struct pid* pid; struct r3964_client_info* next; } ;
struct pid {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct r3964_client_info *findClient(struct r3964_info *pInfo,
		struct pid *pid)
{
	struct r3964_client_info *pClient;

	for (pClient = pInfo->firstClient; pClient; pClient = pClient->next) {
		if (pClient->pid == pid) {
			return pClient;
		}
	}
	return NULL;
}