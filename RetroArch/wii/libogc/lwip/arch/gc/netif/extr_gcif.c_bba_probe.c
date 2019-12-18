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
typedef  scalar_t__ u32 ;
struct netif {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 scalar_t__ BBA_CID ; 
 int /*<<< orphan*/  ERR_NODEV ; 
 scalar_t__ __bba_read_cid () ; 
 int /*<<< orphan*/  bba_init_one (struct netif*) ; 

__attribute__((used)) static err_t bba_probe(struct netif *dev)
{
	u32 cid;
	err_t ret;

	cid = __bba_read_cid();
	if(cid!=BBA_CID) return ERR_NODEV;

	ret = bba_init_one(dev);
	return ret;
}