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
struct pfi_kif_cmp {int /*<<< orphan*/  pfik_name; } ;
struct pfi_kif {int /*<<< orphan*/  pfik_dynaddrs; int /*<<< orphan*/  pfik_tzero; int /*<<< orphan*/  pfik_name; } ;
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PFI_MTYPE ; 
 struct pfi_kif* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfi_kif*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfi_kif*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct pfi_kif* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct pfi_kif_cmp*,int) ; 
 int /*<<< orphan*/  pf_calendar_time_second () ; 
 int /*<<< orphan*/  pfi_ifhead ; 
 int /*<<< orphan*/  pfi_ifs ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

struct pfi_kif *
pfi_kif_get(const char *kif_name)
{
	struct pfi_kif		*kif;
	struct pfi_kif_cmp	 s;

	bzero(&s, sizeof (s));
	strlcpy(s.pfik_name, kif_name, sizeof (s.pfik_name));
	if ((kif = RB_FIND(pfi_ifhead, &pfi_ifs,
	    (struct pfi_kif *)(void *)&s)) != NULL)
		return (kif);

	/* create new one */
	if ((kif = _MALLOC(sizeof (*kif), PFI_MTYPE, M_WAITOK|M_ZERO)) == NULL)
		return (NULL);

	strlcpy(kif->pfik_name, kif_name, sizeof (kif->pfik_name));
	kif->pfik_tzero = pf_calendar_time_second();
	TAILQ_INIT(&kif->pfik_dynaddrs);

	RB_INSERT(pfi_ifhead, &pfi_ifs, kif);
	return (kif);
}