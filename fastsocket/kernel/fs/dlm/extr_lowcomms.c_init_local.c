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
struct sockaddr_storage {int dummy; } ;

/* Variables and functions */
 int DLM_MAX_ADDR_COUNT ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct sockaddr_storage** dlm_local_addr ; 
 scalar_t__ dlm_local_count ; 
 scalar_t__ dlm_our_addr (struct sockaddr_storage*,int) ; 
 struct sockaddr_storage* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,struct sockaddr_storage*,int) ; 

__attribute__((used)) static void init_local(void)
{
	struct sockaddr_storage sas, *addr;
	int i;

	dlm_local_count = 0;
	for (i = 0; i < DLM_MAX_ADDR_COUNT - 1; i++) {
		if (dlm_our_addr(&sas, i))
			break;

		addr = kmalloc(sizeof(*addr), GFP_NOFS);
		if (!addr)
			break;
		memcpy(addr, &sas, sizeof(*addr));
		dlm_local_addr[dlm_local_count++] = addr;
	}
}