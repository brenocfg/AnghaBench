#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {scalar_t__ segmentpos; int /*<<< orphan*/  elementid; } ;
typedef  TYPE_1__ mkv_seekhead_entry ;
struct TYPE_7__ {scalar_t__ max_entries; scalar_t__ num_entries; scalar_t__ segment_offset; TYPE_1__* entries; } ;
typedef  TYPE_2__ mkv_seekhead ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* av_realloc_array (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static int mkv_add_seekhead_entry(mkv_seekhead *seekhead, uint32_t elementid, uint64_t filepos)
{
    mkv_seekhead_entry *entries = seekhead->entries;

    // don't store more elements than we reserved space for
    if (seekhead->max_entries > 0 && seekhead->max_entries <= seekhead->num_entries)
        return -1;

    entries = av_realloc_array(entries, seekhead->num_entries + 1, sizeof(mkv_seekhead_entry));
    if (!entries)
        return AVERROR(ENOMEM);
    seekhead->entries = entries;

    seekhead->entries[seekhead->num_entries].elementid    = elementid;
    seekhead->entries[seekhead->num_entries++].segmentpos = filepos - seekhead->segment_offset;

    return 0;
}