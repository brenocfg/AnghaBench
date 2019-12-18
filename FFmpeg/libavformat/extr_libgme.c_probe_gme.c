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
struct TYPE_3__ {int buf_size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 scalar_t__* gme_identify_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int probe_gme(const AVProbeData *p)
{
    // Reads 4 bytes - returns "" if unknown format.
    if (gme_identify_header(p->buf)[0]) {
        if (p->buf_size < 16384)
            return AVPROBE_SCORE_MAX / 4 ;
        else
            return AVPROBE_SCORE_MAX / 2;
    }
    return 0;
}