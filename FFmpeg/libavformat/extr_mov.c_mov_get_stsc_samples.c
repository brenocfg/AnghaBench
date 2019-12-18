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
typedef  int int64_t ;
struct TYPE_5__ {int chunk_count; TYPE_1__* stsc_data; int /*<<< orphan*/  stsc_count; } ;
struct TYPE_4__ {int first; int count; } ;
typedef  TYPE_2__ MOVStreamContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ mov_stsc_index_valid (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int64_t mov_get_stsc_samples(MOVStreamContext *sc, unsigned int index)
{
    int chunk_count;

    if (mov_stsc_index_valid(index, sc->stsc_count))
        chunk_count = sc->stsc_data[index + 1].first - sc->stsc_data[index].first;
    else {
        // Validation for stsc / stco  happens earlier in mov_read_stsc + mov_read_trak.
        av_assert0(sc->stsc_data[index].first <= sc->chunk_count);
        chunk_count = sc->chunk_count - (sc->stsc_data[index].first - 1);
    }

    return sc->stsc_data[index].count * (int64_t)chunk_count;
}