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
struct TYPE_3__ {int qebeg; int qeend; double ovola; double* qev; size_t curtick; size_t* qet; } ;
typedef  TYPE_1__ PokeyState ;

/* Variables and functions */
 double* filter_data ; 
 int filter_size ; 

__attribute__((used)) static double read_resam_all(PokeyState* ps)
{
    int i = ps->qebeg;
    qev_t avol,bvol;
    double sum;

    if(ps->qebeg == ps->qeend)
    {
        return ps->ovola * filter_data[0]; /* if no events in the queue */
    }

    avol = ps->ovola;
    sum = 0;

    /* Separate two loop cases, for wrap-around and without */
    if(ps->qeend < ps->qebeg) /* With wrap */
    {
        while(i<filter_size)
        {
            bvol = ps->qev[i];
            sum += (avol-bvol)*filter_data[ps->curtick - ps->qet[i]];
            avol = bvol;
            ++i;
        }
        i=0;
    }

    /* without wrap */
    while(i<ps->qeend)
    {
        bvol = ps->qev[i];
        sum += (avol-bvol)*filter_data[ps->curtick - ps->qet[i]];
        avol = bvol;
        ++i;
    }

    sum += avol*filter_data[0];
    return sum;
}