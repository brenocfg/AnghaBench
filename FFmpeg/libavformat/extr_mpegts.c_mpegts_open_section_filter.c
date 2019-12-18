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
struct TYPE_8__ {int check_crc; int last_ver; int /*<<< orphan*/  section_buf; void* opaque; int /*<<< orphan*/ * section_cb; } ;
struct TYPE_7__ {TYPE_2__ section_filter; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  SectionCallback ;
typedef  TYPE_2__ MpegTSSectionFilter ;
typedef  TYPE_3__ MpegTSFilter ;
typedef  int /*<<< orphan*/  MpegTSContext ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SECTION_SIZE ; 
 int /*<<< orphan*/  MPEGTS_SECTION ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 int /*<<< orphan*/  av_mallocz (int /*<<< orphan*/ ) ; 
 TYPE_3__* mpegts_open_filter (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MpegTSFilter *mpegts_open_section_filter(MpegTSContext *ts,
                                                unsigned int pid,
                                                SectionCallback *section_cb,
                                                void *opaque,
                                                int check_crc)
{
    MpegTSFilter *filter;
    MpegTSSectionFilter *sec;

    if (!(filter = mpegts_open_filter(ts, pid, MPEGTS_SECTION)))
        return NULL;
    sec = &filter->u.section_filter;
    sec->section_cb  = section_cb;
    sec->opaque      = opaque;
    sec->section_buf = av_mallocz(MAX_SECTION_SIZE);
    sec->check_crc   = check_crc;
    sec->last_ver    = -1;

    if (!sec->section_buf) {
        av_free(filter);
        return NULL;
    }
    return filter;
}