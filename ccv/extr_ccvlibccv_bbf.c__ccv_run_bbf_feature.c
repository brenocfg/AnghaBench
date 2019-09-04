#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t* pz; int* px; int* py; size_t* nz; int* nx; int* ny; int size; } ;
typedef  TYPE_1__ ccv_bbf_feature_t ;

/* Variables and functions */

__attribute__((used)) static inline int _ccv_run_bbf_feature(ccv_bbf_feature_t* feature, int* step, unsigned char** u8)
{
#define pf_at(i) (*(u8[feature->pz[i]] + feature->px[i] + feature->py[i] * step[feature->pz[i]]))
#define nf_at(i) (*(u8[feature->nz[i]] + feature->nx[i] + feature->ny[i] * step[feature->nz[i]]))
	unsigned char pmin = pf_at(0), nmax = nf_at(0);
	/* check if every point in P > every point in N, and take a shortcut */
	if (pmin <= nmax)
		return 0;
	int i;
	for (i = 1; i < feature->size; i++)
	{
		if (feature->pz[i] >= 0)
		{
			int p = pf_at(i);
			if (p < pmin)
			{
				if (p <= nmax)
					return 0;
				pmin = p;
			}
		}
		if (feature->nz[i] >= 0)
		{
			int n = nf_at(i);
			if (n > nmax)
			{
				if (pmin <= n)
					return 0;
				nmax = n;
			}
		}
	}
#undef pf_at
#undef nf_at
	return 1;
}