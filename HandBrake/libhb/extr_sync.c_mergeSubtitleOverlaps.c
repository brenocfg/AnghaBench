#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  list_current; } ;
typedef  TYPE_2__ subtitle_sanitizer_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_16__ {int flags; scalar_t__ start; scalar_t__ stop; } ;
struct TYPE_18__ {TYPE_1__ s; struct TYPE_18__* next; } ;
typedef  TYPE_3__ hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int HB_BUF_FLAG_EOF ; 
 scalar_t__ INT64_MAX ; 
 TYPE_3__* findOverlap (TYPE_2__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_3__**) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 TYPE_3__* hb_buffer_list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_buffer_list_prepend (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  hb_buffer_list_rem (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* merge_ssa (TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static int mergeSubtitleOverlaps(subtitle_sanitizer_t *sanitizer)
{
    hb_buffer_t  * merged_buf   = NULL;
    hb_buffer_t  * a, * b;

    a = hb_buffer_list_head(&sanitizer->list_current);
    if (a != NULL && (a->s.flags & HB_BUF_FLAG_EOF))
    {
        // EOF
        return 0;
    }
    if (a == NULL ||
        a->s.start == AV_NOPTS_VALUE || a->s.stop == AV_NOPTS_VALUE)
    {
        // Not enough information to resolve an overlap
        return -1;
    }
    b = a->next;
    if (b != NULL && a->s.stop <= b->s.start)
    {
        // No overlap
        return 0;
    }

    // Check that we have 2 non-overlapping buffers in the list
    // and that all timestamps are valid up to the non-overlap.
    // This ensures that multiple overlapping subtitles have been
    // completely merged.
    while (b != NULL &&
           b->s.start < a->s.stop && !(b->s.flags & HB_BUF_FLAG_EOF))
    {
        if (b->s.start == AV_NOPTS_VALUE || b->s.stop == AV_NOPTS_VALUE)
        {
            // Not enough information to resolve an overlap
            return -1;
        }
        b = b->next;
    }
    if (b == NULL)
    {
        // Not enough information to resolve an overlap
        return -1;
    }

    hb_buffer_list_t   merged_list;
    int64_t            start, stop, last;

    if (b->s.flags & HB_BUF_FLAG_EOF)
    {
        last = INT64_MAX;
    }
    else
    {
        last = b->s.start;
    }

    hb_buffer_list_clear(&merged_list);
    a = hb_buffer_list_head(&sanitizer->list_current);
    stop = start = a->s.start;
    while (start < last)
    {
        hb_buffer_t * merge = findOverlap(sanitizer, start, &stop);
        if (merge == NULL)
        {
            break;
        }
        a = merge;
        merged_buf = NULL;
        while (a != NULL)
        {
            hb_buffer_t * tmp;

            tmp = merge_ssa(merged_buf, a);
            hb_buffer_close(&merged_buf);
            merged_buf = tmp;

            a = a->next;
        }
        merged_buf->s.stop = stop;
        hb_buffer_close(&merge);
        hb_buffer_list_append(&merged_list, merged_buf);
        start = stop;

        // Remove merged buffers
        a = hb_buffer_list_head(&sanitizer->list_current);
        while (a != NULL && a->s.start < stop &&
               !(a->s.flags & HB_BUF_FLAG_EOF))
        {
            hb_buffer_t * next = a->next;
            if (a->s.stop <= stop)
            {
                // Buffer consumed
                hb_buffer_list_rem(&sanitizer->list_current, a);
                hb_buffer_close(&a);
            }
            else
            {
                a->s.start = stop;
            }
            a = next;
        }
    }
    merged_buf = hb_buffer_list_clear(&merged_list);
    hb_buffer_list_prepend(&sanitizer->list_current, merged_buf);

    return 0;
}