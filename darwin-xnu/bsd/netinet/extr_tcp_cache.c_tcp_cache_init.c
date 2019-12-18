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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct tcp_heuristics_head {int dummy; } ;
struct tcp_cache_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tcp_caches; int /*<<< orphan*/  tch_mtx; } ;
struct TYPE_3__ {int /*<<< orphan*/  tcp_heuristics; int /*<<< orphan*/  thh_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_ZERO ; 
 int /*<<< orphan*/  RandomULong () ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 void* _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int sane_size ; 
 TYPE_2__* tcp_cache ; 
 int /*<<< orphan*/  tcp_cache_hash_seed ; 
 int /*<<< orphan*/  tcp_cache_mtx_attr ; 
 int /*<<< orphan*/  tcp_cache_mtx_grp ; 
 int /*<<< orphan*/  tcp_cache_mtx_grp_attr ; 
 int tcp_cache_roundup2 (int /*<<< orphan*/ ) ; 
 int tcp_cache_size ; 
 int /*<<< orphan*/  tcp_heuristic_mtx_attr ; 
 int /*<<< orphan*/  tcp_heuristic_mtx_grp ; 
 int /*<<< orphan*/  tcp_heuristic_mtx_grp_attr ; 
 TYPE_1__* tcp_heuristics ; 

void tcp_cache_init(void)
{
	uint64_t sane_size_meg = sane_size / 1024 / 1024;
	int i;

	/*
	 * On machines with <100MB of memory this will result in a (full) cache-size
	 * of 32 entries, thus 32 * 5 * 64bytes = 10KB. (about 0.01 %)
	 * On machines with > 4GB of memory, we have a cache-size of 1024 entries,
	 * thus about 327KB.
	 *
	 * Side-note: we convert to u_int32_t. If sane_size is more than
	 * 16000 TB, we loose precision. But, who cares? :)
	 */
	tcp_cache_size = tcp_cache_roundup2((u_int32_t)(sane_size_meg >> 2));
	if (tcp_cache_size < 32)
		tcp_cache_size = 32;
	else if (tcp_cache_size > 1024)
		tcp_cache_size = 1024;

	tcp_cache = _MALLOC(sizeof(struct tcp_cache_head) * tcp_cache_size,
	    M_TEMP, M_ZERO);
	if (tcp_cache == NULL)
		panic("Allocating tcp_cache failed at boot-time!");

	tcp_cache_mtx_grp_attr = lck_grp_attr_alloc_init();
	tcp_cache_mtx_grp = lck_grp_alloc_init("tcpcache", tcp_cache_mtx_grp_attr);
	tcp_cache_mtx_attr = lck_attr_alloc_init();

	tcp_heuristics = _MALLOC(sizeof(struct tcp_heuristics_head) * tcp_cache_size,
	    M_TEMP, M_ZERO);
	if (tcp_heuristics == NULL)
		panic("Allocating tcp_heuristic failed at boot-time!");

	tcp_heuristic_mtx_grp_attr = lck_grp_attr_alloc_init();
	tcp_heuristic_mtx_grp = lck_grp_alloc_init("tcpheuristic", tcp_heuristic_mtx_grp_attr);
	tcp_heuristic_mtx_attr = lck_attr_alloc_init();

	for (i = 0; i < tcp_cache_size; i++) {
		lck_mtx_init(&tcp_cache[i].tch_mtx, tcp_cache_mtx_grp,
		    tcp_cache_mtx_attr);
		SLIST_INIT(&tcp_cache[i].tcp_caches);

		lck_mtx_init(&tcp_heuristics[i].thh_mtx, tcp_heuristic_mtx_grp,
		    tcp_heuristic_mtx_attr);
		SLIST_INIT(&tcp_heuristics[i].tcp_heuristics);
	}

	tcp_cache_hash_seed = RandomULong();
}