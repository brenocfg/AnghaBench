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
struct nvlist_prtctl {int dummy; } ;
struct nvlist_printops {int dummy; } ;
typedef  struct nvlist_prtctl* nvlist_prtctl_t ;

/* Variables and functions */
 struct nvlist_printops* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct nvlist_prtctl*) ; 
 struct nvlist_prtctl* malloc (int) ; 
 int /*<<< orphan*/  prtctl_defaults (int /*<<< orphan*/ ,struct nvlist_prtctl*,struct nvlist_printops*) ; 
 int /*<<< orphan*/  stdout ; 

nvlist_prtctl_t
nvlist_prtctl_alloc(void)
{
	struct nvlist_prtctl *pctl;
	struct nvlist_printops *ops;

	if ((pctl = malloc(sizeof (*pctl))) == NULL)
		return (NULL);

	if ((ops = calloc(1, sizeof (*ops))) == NULL) {
		free(pctl);
		return (NULL);
	}

	prtctl_defaults(stdout, pctl, ops);

	return (pctl);
}