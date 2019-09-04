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
typedef  int uint64_t ;
struct TYPE_5__ {int size; int chunkNum; scalar_t__ pos; scalar_t__ entries; int /*<<< orphan*/  samples_in_chunk; } ;
struct TYPE_4__ {int chunkCount; int entry; TYPE_2__* cluster; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  TYPE_2__ MOVIentry ;

/* Variables and functions */

__attribute__((used)) static void build_chunks(MOVTrack *trk)
{
    int i;
    MOVIentry *chunk = &trk->cluster[0];
    uint64_t chunkSize = chunk->size;
    chunk->chunkNum = 1;
    if (trk->chunkCount)
        return;
    trk->chunkCount = 1;
    for (i = 1; i<trk->entry; i++){
        if (chunk->pos + chunkSize == trk->cluster[i].pos &&
            chunkSize + trk->cluster[i].size < (1<<20)){
            chunkSize             += trk->cluster[i].size;
            chunk->samples_in_chunk += trk->cluster[i].entries;
        } else {
            trk->cluster[i].chunkNum = chunk->chunkNum+1;
            chunk=&trk->cluster[i];
            chunkSize = chunk->size;
            trk->chunkCount++;
        }
    }
}