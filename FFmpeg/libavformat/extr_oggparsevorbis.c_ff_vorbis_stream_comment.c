#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  event_flags; int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVSTREAM_EVENT_FLAG_METADATA_UPDATED ; 
 int ff_vorbis_comment (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 

int ff_vorbis_stream_comment(AVFormatContext *as, AVStream *st,
                             const uint8_t *buf, int size)
{
    int updates = ff_vorbis_comment(as, &st->metadata, buf, size, 1);

    if (updates > 0) {
        st->event_flags |= AVSTREAM_EVENT_FLAG_METADATA_UPDATED;
    }

    return updates;
}