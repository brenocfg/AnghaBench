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
struct ping_table {struct hlist_nulls_head* hash; } ;
struct net {int dummy; } ;
struct hlist_nulls_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PING_HTABLE_MASK ; 
 size_t ping_hashfn (struct net*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct hlist_nulls_head *ping_hashslot(struct ping_table *table,
					     struct net *net, unsigned num)
{
	return &table->hash[ping_hashfn(net, num, PING_HTABLE_MASK)];
}