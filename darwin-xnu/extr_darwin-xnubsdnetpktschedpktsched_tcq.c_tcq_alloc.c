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
struct tcq_if {int tif_maxpri; int /*<<< orphan*/ * tif_ifq; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct tcq_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pktsched_verbose ; 
 int /*<<< orphan*/  tcq_size ; 
 int /*<<< orphan*/  tcq_style (struct tcq_if*) ; 
 int /*<<< orphan*/  tcq_zone ; 
 struct tcq_if* zalloc (int /*<<< orphan*/ ) ; 
 struct tcq_if* zalloc_noblock (int /*<<< orphan*/ ) ; 

struct tcq_if *
tcq_alloc(struct ifnet *ifp, int how)
{
	struct tcq_if	*tif;

	tif = (how == M_WAITOK) ? zalloc(tcq_zone) : zalloc_noblock(tcq_zone);
	if (tif == NULL)
		return (NULL);

	bzero(tif, tcq_size);
	tif->tif_maxpri = -1;
	tif->tif_ifq = &ifp->if_snd;

	if (pktsched_verbose) {
		log(LOG_DEBUG, "%s: %s scheduler allocated\n",
		    if_name(ifp), tcq_style(tif));
	}

	return (tif);
}