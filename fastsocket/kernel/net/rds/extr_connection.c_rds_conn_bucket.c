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
struct hlist_head {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned long RDS_CONNECTION_HASH_MASK ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long inet_ehashfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hlist_head* rds_conn_hash ; 

__attribute__((used)) static struct hlist_head *rds_conn_bucket(__be32 laddr, __be32 faddr)
{
	/* Pass NULL, don't need struct net for hash */
	unsigned long hash = inet_ehashfn(NULL,
					  be32_to_cpu(laddr), 0,
					  be32_to_cpu(faddr), 0);
	return &rds_conn_hash[hash & RDS_CONNECTION_HASH_MASK];
}