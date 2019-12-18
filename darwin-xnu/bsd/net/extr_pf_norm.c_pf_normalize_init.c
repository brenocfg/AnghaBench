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
struct pf_state_scrub {int dummy; } ;
struct pf_frent {int dummy; } ;
struct pf_frcache {int dummy; } ;
struct pf_fragment {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFFRAG_FRAG_HIWAT ; 
 int /*<<< orphan*/  PFFRAG_FRCACHE_HIWAT ; 
 int /*<<< orphan*/  PFFRAG_FRCENT_HIWAT ; 
 int /*<<< orphan*/  PFFRAG_FRENT_HIWAT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_cache_pl ; 
 int /*<<< orphan*/  pf_cachequeue ; 
 int /*<<< orphan*/  pf_cent_pl ; 
 int /*<<< orphan*/  pf_frag_pl ; 
 int /*<<< orphan*/  pf_fragqueue ; 
 int /*<<< orphan*/  pf_frent_pl ; 
 int /*<<< orphan*/  pf_state_scrub_pl ; 
 int /*<<< orphan*/  pool_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pool_sethardlimit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_sethiwat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pf_normalize_init(void)
{
	pool_init(&pf_frent_pl, sizeof (struct pf_frent), 0, 0, 0, "pffrent",
	    NULL);
	pool_init(&pf_frag_pl, sizeof (struct pf_fragment), 0, 0, 0, "pffrag",
	    NULL);
	pool_init(&pf_cache_pl, sizeof (struct pf_fragment), 0, 0, 0,
	    "pffrcache", NULL);
	pool_init(&pf_cent_pl, sizeof (struct pf_frcache), 0, 0, 0, "pffrcent",
	    NULL);
	pool_init(&pf_state_scrub_pl, sizeof (struct pf_state_scrub), 0, 0, 0,
	    "pfstscr", NULL);

	pool_sethiwat(&pf_frag_pl, PFFRAG_FRAG_HIWAT);
	pool_sethardlimit(&pf_frent_pl, PFFRAG_FRENT_HIWAT, NULL, 0);
	pool_sethardlimit(&pf_cache_pl, PFFRAG_FRCACHE_HIWAT, NULL, 0);
	pool_sethardlimit(&pf_cent_pl, PFFRAG_FRCENT_HIWAT, NULL, 0);

	TAILQ_INIT(&pf_fragqueue);
	TAILQ_INIT(&pf_cachequeue);
}