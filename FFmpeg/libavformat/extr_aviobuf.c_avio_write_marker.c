#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  enum AVIODataMarkerType { ____Placeholder_AVIODataMarkerType } AVIODataMarkerType ;
struct TYPE_4__ {scalar_t__ buf_ptr; scalar_t__ buffer; scalar_t__ min_packet_size; int current_type; int /*<<< orphan*/  last_time; scalar_t__ ignore_boundary_point; int /*<<< orphan*/  write_data_type; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int AVIO_DATA_MARKER_BOUNDARY_POINT ; 
 int AVIO_DATA_MARKER_FLUSH_POINT ; 
#define  AVIO_DATA_MARKER_HEADER 129 
#define  AVIO_DATA_MARKER_TRAILER 128 
 int AVIO_DATA_MARKER_UNKNOWN ; 
 int /*<<< orphan*/  avio_flush (TYPE_1__*) ; 

void avio_write_marker(AVIOContext *s, int64_t time, enum AVIODataMarkerType type)
{
    if (type == AVIO_DATA_MARKER_FLUSH_POINT) {
        if (s->buf_ptr - s->buffer >= s->min_packet_size)
            avio_flush(s);
        return;
    }
    if (!s->write_data_type)
        return;
    // If ignoring boundary points, just treat it as unknown
    if (type == AVIO_DATA_MARKER_BOUNDARY_POINT && s->ignore_boundary_point)
        type = AVIO_DATA_MARKER_UNKNOWN;
    // Avoid unnecessary flushes if we are already in non-header/trailer
    // data and setting the type to unknown
    if (type == AVIO_DATA_MARKER_UNKNOWN &&
        (s->current_type != AVIO_DATA_MARKER_HEADER &&
         s->current_type != AVIO_DATA_MARKER_TRAILER))
        return;

    switch (type) {
    case AVIO_DATA_MARKER_HEADER:
    case AVIO_DATA_MARKER_TRAILER:
        // For header/trailer, ignore a new marker of the same type;
        // consecutive header/trailer markers can be merged.
        if (type == s->current_type)
            return;
        break;
    }

    // If we've reached here, we have a new, noteworthy marker.
    // Flush the previous data and mark the start of the new data.
    avio_flush(s);
    s->current_type = type;
    s->last_time = time;
}