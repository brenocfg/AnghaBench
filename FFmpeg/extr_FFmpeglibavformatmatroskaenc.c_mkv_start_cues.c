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
struct TYPE_4__ {int /*<<< orphan*/  segment_offset; } ;
typedef  TYPE_1__ mkv_cues ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 TYPE_1__* av_mallocz (int) ; 

__attribute__((used)) static mkv_cues *mkv_start_cues(int64_t segment_offset)
{
    mkv_cues *cues = av_mallocz(sizeof(mkv_cues));
    if (!cues)
        return NULL;

    cues->segment_offset = segment_offset;
    return cues;
}