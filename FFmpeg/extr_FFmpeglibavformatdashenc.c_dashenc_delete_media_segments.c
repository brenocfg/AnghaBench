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
struct TYPE_7__ {int /*<<< orphan*/  file; } ;
struct TYPE_6__ {int nb_segments; TYPE_2__** segments; } ;
typedef  TYPE_1__ OutputStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_2__*) ; 
 int /*<<< orphan*/  dashenc_delete_segment_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_2__**,TYPE_2__**,int) ; 

__attribute__((used)) static inline void dashenc_delete_media_segments(AVFormatContext *s, OutputStream *os, int remove_count)
{
    for (int i = 0; i < remove_count; ++i) {
        dashenc_delete_segment_file(s, os->segments[i]->file);

        // Delete the segment regardless of whether the file was successfully deleted
        av_free(os->segments[i]);
    }

    os->nb_segments -= remove_count;
    memmove(os->segments, os->segments + remove_count, os->nb_segments * sizeof(*os->segments));
}