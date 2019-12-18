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
typedef  int /*<<< orphan*/  u64 ;
struct hpsb_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  csr_highlevel ; 
 int /*<<< orphan*/  hpsb_unregister_addrspace (int /*<<< orphan*/ *,struct hpsb_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_addr_range(u64 addr, void *__host)
{
 	struct hpsb_host *host = (struct hpsb_host*)__host;
	hpsb_unregister_addrspace(&csr_highlevel, host, addr);
}