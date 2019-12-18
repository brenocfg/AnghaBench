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
struct TYPE_3__ {int /*<<< orphan*/ * blocksize; int /*<<< orphan*/  previous_blocksize; scalar_t__ valid_extradata; } ;
typedef  TYPE_1__ AVVorbisParseContext ;

/* Variables and functions */

void av_vorbis_parse_reset(AVVorbisParseContext *s)
{
    if (s->valid_extradata)
        s->previous_blocksize = s->blocksize[0];
}