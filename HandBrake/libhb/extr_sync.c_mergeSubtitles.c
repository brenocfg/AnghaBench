#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  list_current; int /*<<< orphan*/  merge; } ;
struct TYPE_16__ {TYPE_4__ sanitizer; } ;
struct TYPE_18__ {TYPE_1__ subtitle; } ;
typedef  TYPE_3__ sync_stream_t ;
typedef  TYPE_4__ subtitle_sanitizer_t ;
struct TYPE_17__ {int flags; scalar_t__ stop; } ;
struct TYPE_20__ {TYPE_2__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int HB_BUF_FLAG_EOF ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_5__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_buffer_list_count (int /*<<< orphan*/ *) ; 
 TYPE_5__* hb_buffer_list_head (int /*<<< orphan*/ *) ; 
 TYPE_5__* hb_buffer_list_rem_head (int /*<<< orphan*/ *) ; 
 int mergeSubtitleOverlaps (TYPE_4__*) ; 
 TYPE_5__* setSubDuration (TYPE_3__*,TYPE_5__*) ; 

__attribute__((used)) static hb_buffer_t * mergeSubtitles(sync_stream_t * stream)
{
    hb_buffer_t          * buf;
    hb_buffer_list_t       list;
    subtitle_sanitizer_t * sanitizer = &stream->subtitle.sanitizer;

    hb_buffer_list_clear(&list);

    if (!sanitizer->merge)
    {
        // Handle all but the last buffer
        // The last buffer may not have been "linked" yet
        while (hb_buffer_list_count(&sanitizer->list_current) > 0)
        {
            buf = hb_buffer_list_head(&sanitizer->list_current);
            if (!(buf->s.flags & HB_BUF_FLAG_EOF) &&
                buf->s.stop != AV_NOPTS_VALUE)
            {
                buf = hb_buffer_list_rem_head(&sanitizer->list_current);
                buf = setSubDuration(stream, buf);
                hb_buffer_list_append(&list, buf);
            }
            else
            {
                break;
            }
        }
        return hb_buffer_list_clear(&list);
    }

    // We only reach here if we are merging subtitles
    while (hb_buffer_list_count(&sanitizer->list_current) > 0)
    {
        buf = hb_buffer_list_head(&sanitizer->list_current);
        if (buf->s.flags & HB_BUF_FLAG_EOF)
        {
            // remove EOF from list, add to output
            buf = hb_buffer_list_rem_head(&sanitizer->list_current);
            hb_buffer_list_append(&list, buf);
            break;
        }

        int result = mergeSubtitleOverlaps(sanitizer);
        if (result < 0)
        {
            // not enough information available yet to resolve the overlap
            break;
        }

        // Overlap resolved, output a buffer
        buf = hb_buffer_list_rem_head(&sanitizer->list_current);
        if (buf != NULL && !(buf->s.flags & HB_BUF_FLAG_EOF))
        {
            buf = setSubDuration(stream, buf);
            hb_buffer_list_append(&list, buf);
        }
    }

    return hb_buffer_list_clear(&list);
}