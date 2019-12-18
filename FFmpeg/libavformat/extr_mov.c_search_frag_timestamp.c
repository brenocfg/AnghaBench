#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {int id; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int nb_items; } ;
struct TYPE_7__ {scalar_t__ has_sidx; } ;
typedef  TYPE_1__ MOVStreamContext ;
typedef  TYPE_2__ MOVFragmentIndex ;
typedef  TYPE_3__ AVStream ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ get_frag_time (TYPE_2__*,int,int) ; 

__attribute__((used)) static int search_frag_timestamp(MOVFragmentIndex *frag_index,
                                 AVStream *st, int64_t timestamp)
{
    int a, b, m, m0;
    int64_t frag_time;
    int id = -1;

    if (st) {
        // If the stream is referenced by any sidx, limit the search
        // to fragments that referenced this stream in the sidx
        MOVStreamContext *sc = st->priv_data;
        if (sc->has_sidx)
            id = st->id;
    }

    a = -1;
    b = frag_index->nb_items;

    while (b - a > 1) {
        m0 = m = (a + b) >> 1;

        while (m < b &&
               (frag_time = get_frag_time(frag_index, m, id)) == AV_NOPTS_VALUE)
            m++;

        if (m < b && frag_time <= timestamp)
            a = m;
        else
            b = m0;
    }

    return a;
}