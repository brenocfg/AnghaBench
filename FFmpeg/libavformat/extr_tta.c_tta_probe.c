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
struct TYPE_3__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RL16 (int /*<<< orphan*/ *) ; 
 scalar_t__ AV_RL32 (int /*<<< orphan*/ *) ; 
 scalar_t__ MKTAG (char,char,char,char) ; 

__attribute__((used)) static int tta_probe(const AVProbeData *p)
{
    if (AV_RL32(&p->buf[0]) == MKTAG('T', 'T', 'A', '1') &&
        (AV_RL16(&p->buf[4]) == 1 || AV_RL16(&p->buf[4]) == 2) &&
        AV_RL16(&p->buf[6]) > 0 &&
        AV_RL16(&p->buf[8]) > 0 &&
        AV_RL32(&p->buf[10]) > 0)
        return AVPROBE_SCORE_EXTENSION + 30;
    return 0;
}