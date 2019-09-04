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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int nb_index_entries; TYPE_1__* index_entries; int /*<<< orphan*/  pts; int /*<<< orphan*/ * pb; } ;
typedef  TYPE_2__ WtvContext ;
struct TYPE_4__ {scalar_t__ pos; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recover(WtvContext *wtv, uint64_t broken_pos)
{
    AVIOContext *pb = wtv->pb;
    int i;
    for (i = 0; i < wtv->nb_index_entries; i++) {
        if (wtv->index_entries[i].pos > broken_pos) {
            int64_t ret = avio_seek(pb, wtv->index_entries[i].pos, SEEK_SET);
            if (ret < 0)
                return ret;
            wtv->pts = wtv->index_entries[i].timestamp;
            return 0;
         }
     }
     return AVERROR(EIO);
}