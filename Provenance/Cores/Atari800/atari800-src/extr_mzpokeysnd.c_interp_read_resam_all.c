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
typedef  double qev_t ;
struct TYPE_3__ {int qebeg; int qeend; double ovola; double* qev; scalar_t__* qet; scalar_t__ curtick; } ;
typedef  TYPE_1__ PokeyState ;

/* Variables and functions */
 int filter_size ; 
 double interp_filter_data (scalar_t__,double) ; 

__attribute__((used)) static double interp_read_resam_all(PokeyState* ps, double frac)
{
    int i = ps->qebeg;
    qev_t avol,bvol;
    double sum;

    if (ps->qebeg == ps->qeend)
    {
        return ps->ovola * interp_filter_data(0,frac); /* if no events in the queue */
    }

    avol = ps->ovola;
    sum = 0;

    /* Separate two loop cases, for wrap-around and without */
    if (ps->qeend < ps->qebeg) /* With wrap */
    {
        while (i < filter_size)
        {
            bvol = ps->qev[i];
            sum += (avol-bvol)*interp_filter_data(ps->curtick - ps->qet[i],frac);
            avol = bvol;
            ++i;
        }
        i = 0;
    }

    /* without wrap */
    while (i < ps->qeend)
    {
        bvol = ps->qev[i];
        sum += (avol-bvol)*interp_filter_data(ps->curtick - ps->qet[i],frac);
        avol = bvol;
        ++i;
    }

    sum += avol*interp_filter_data(0,frac);

    return sum;
}