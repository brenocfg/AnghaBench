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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ HLSSegment ;

/* Variables and functions */
 int /*<<< orphan*/  av_strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static HLSSegment *find_segment_by_filename(HLSSegment *segment, const char *filename)
{
    while (segment) {
        if (!av_strcasecmp(segment->filename,filename))
            return segment;
        segment = segment->next;
    }
    return (HLSSegment *) NULL;
}