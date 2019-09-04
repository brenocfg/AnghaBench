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
struct nd6_prproxy_solsrc {int dummy; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct nd6_prproxy_solsrc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solsrc_size ; 
 int /*<<< orphan*/  solsrc_zone ; 
 struct nd6_prproxy_solsrc* zalloc (int /*<<< orphan*/ ) ; 
 struct nd6_prproxy_solsrc* zalloc_noblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nd6_prproxy_solsrc *
nd6_solsrc_alloc(int how)
{
	struct nd6_prproxy_solsrc *ssrc;

	ssrc = (how == M_WAITOK) ? zalloc(solsrc_zone) :
	    zalloc_noblock(solsrc_zone);
	if (ssrc != NULL)
		bzero(ssrc, solsrc_size);

	return (ssrc);
}