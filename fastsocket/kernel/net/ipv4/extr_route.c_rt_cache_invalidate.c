#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rt_genid; } ;
struct net {TYPE_1__ ipv4; } ;
typedef  int /*<<< orphan*/  shuffle ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_bytes (unsigned char*,int) ; 

__attribute__((used)) static void rt_cache_invalidate(struct net *net)
{
	unsigned char shuffle;

	get_random_bytes(&shuffle, sizeof(shuffle));
	atomic_add(shuffle + 1U, &net->ipv4.rt_genid);
}