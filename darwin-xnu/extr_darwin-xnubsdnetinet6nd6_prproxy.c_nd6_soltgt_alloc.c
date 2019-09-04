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
struct nd6_prproxy_soltgt {int /*<<< orphan*/  soltgt_q; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct nd6_prproxy_soltgt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soltgt_size ; 
 int /*<<< orphan*/  soltgt_zone ; 
 struct nd6_prproxy_soltgt* zalloc (int /*<<< orphan*/ ) ; 
 struct nd6_prproxy_soltgt* zalloc_noblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nd6_prproxy_soltgt *
nd6_soltgt_alloc(int how)
{
	struct nd6_prproxy_soltgt *soltgt;

	soltgt = (how == M_WAITOK) ? zalloc(soltgt_zone) :
	    zalloc_noblock(soltgt_zone);
	if (soltgt != NULL) {
		bzero(soltgt, soltgt_size);
		TAILQ_INIT(&soltgt->soltgt_q);
	}
	return (soltgt);
}