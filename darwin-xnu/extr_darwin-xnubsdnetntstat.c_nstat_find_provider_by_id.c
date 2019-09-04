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
struct nstat_provider {scalar_t__ nstat_provider_id; struct nstat_provider* next; } ;
typedef  scalar_t__ nstat_provider_id_t ;

/* Variables and functions */
 struct nstat_provider* nstat_providers ; 

__attribute__((used)) static struct nstat_provider*
nstat_find_provider_by_id(
	nstat_provider_id_t	id)
{
	struct nstat_provider	*provider;

	for (provider = nstat_providers; provider != NULL; provider = provider->next)
	{
		if (provider->nstat_provider_id == id)
			break;
	}

	return provider;
}