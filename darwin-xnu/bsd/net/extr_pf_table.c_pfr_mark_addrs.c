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
typedef  int /*<<< orphan*/  w ;
struct pfr_walktree {int /*<<< orphan*/  pfrw_op; } ;
struct pfr_ktable {TYPE_1__* pfrkt_ip6; TYPE_2__* pfrkt_ip4; } ;
struct TYPE_4__ {scalar_t__ (* rnh_walktree ) (TYPE_2__*,int /*<<< orphan*/ ,struct pfr_walktree*) ;} ;
struct TYPE_3__ {scalar_t__ (* rnh_walktree ) (TYPE_1__*,int /*<<< orphan*/ ,struct pfr_walktree*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PFRW_MARK ; 
 int /*<<< orphan*/  bzero (struct pfr_walktree*,int) ; 
 int /*<<< orphan*/  pfr_walktree ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ,struct pfr_walktree*) ; 
 scalar_t__ stub2 (TYPE_1__*,int /*<<< orphan*/ ,struct pfr_walktree*) ; 

__attribute__((used)) static void
pfr_mark_addrs(struct pfr_ktable *kt)
{
	struct pfr_walktree	w;

	bzero(&w, sizeof (w));
	w.pfrw_op = PFRW_MARK;
	if (kt->pfrkt_ip4->rnh_walktree(kt->pfrkt_ip4, pfr_walktree, &w))
		printf("pfr_mark_addrs: IPv4 walktree failed.\n");
	if (kt->pfrkt_ip6->rnh_walktree(kt->pfrkt_ip6, pfr_walktree, &w))
		printf("pfr_mark_addrs: IPv6 walktree failed.\n");
}