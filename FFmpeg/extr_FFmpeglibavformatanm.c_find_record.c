#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nb_records; TYPE_1__* pt; } ;
struct TYPE_4__ {int nb_records; int base_record; } ;
typedef  TYPE_1__ Page ;
typedef  TYPE_2__ AnmDemuxContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int MAX_PAGES ; 

__attribute__((used)) static int find_record(const AnmDemuxContext *anm, int record)
{
    int i;

    if (record >= anm->nb_records)
        return AVERROR_EOF;

    for (i = 0; i < MAX_PAGES; i++) {
        const Page *p = &anm->pt[i];
        if (p->nb_records > 0 && record >= p->base_record && record < p->base_record + p->nb_records)
            return i;
    }

    return AVERROR_INVALIDDATA;
}