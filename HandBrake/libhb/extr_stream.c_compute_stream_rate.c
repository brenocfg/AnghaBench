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
typedef  long long uint64_t ;
struct pts_pos {scalar_t__ pts; scalar_t__ pos; } ;
typedef  int /*<<< orphan*/  rates ;

/* Variables and functions */
 int NDURSAMPLES ; 
 int /*<<< orphan*/  dur_compare ; 
 int /*<<< orphan*/  qsort (double*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static double compute_stream_rate( struct pts_pos *pp, int n )
{
    int i, j;
    double rates[NDURSAMPLES * NDURSAMPLES / 8];
    double *rp = rates;

    // the following nested loops compute the rates between all pairs.
    *rp = 0;
    for ( i = 0; i < n-1; ++i )
    {
        // Bias the median filter by not including pairs that are "far"
        // from one another. This is to handle cases where the file is
        // made of roughly equal size pieces where a symmetric choice of
        // pairs results in having the same number of intra-piece &
        // inter-piece rate estimates. This would mean that the median
        // could easily fall in the inter-piece part of the data which
        // would give a bogus estimate. The 'ns' index creates an
        // asymmetry that favors locality.
        int ns = i + ( n >> 3 );
        if ( ns > n )
            ns = n;
        for ( j = i+1; j < ns; ++j )
        {
            if ( (uint64_t)(pp[j].pts - pp[i].pts) > 90000LL*3600*6 )
                break;
            if ( pp[j].pts != pp[i].pts && pp[j].pos > pp[i].pos )
            {
                *rp = ((double)( pp[j].pts - pp[i].pts )) /
                      ((double)( pp[j].pos - pp[i].pos ));
                ++rp;
            }
        }
    }
    // now compute and return the median of all the (n*n/2) rates we computed
    // above.
    int nrates = rp - rates;
    qsort( rates, nrates, sizeof (rates[0] ), dur_compare );
    return rates[nrates >> 1];
}