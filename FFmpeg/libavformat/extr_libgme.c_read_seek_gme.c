#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  music_emu; } ;
typedef  TYPE_1__ GMEContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  gme_seek (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_seek_gme(AVFormatContext *s, int stream_idx, int64_t ts, int flags)
{
    GMEContext *gme = s->priv_data;
    if (!gme_seek(gme->music_emu, (int)ts))
        return AVERROR_EXTERNAL;
    return 0;
}