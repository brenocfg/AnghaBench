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
struct TYPE_3__ {int buf_size; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 scalar_t__ av_match_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modplug_extensions ; 

__attribute__((used)) static int modplug_probe(const AVProbeData *p)
{
    if (av_match_ext(p->filename, modplug_extensions)) {
        if (p->buf_size < 16384)
            return AVPROBE_SCORE_EXTENSION/2-1;
        else
            return AVPROBE_SCORE_EXTENSION;
    }
    return 0;
}