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
struct TYPE_3__ {int buf_size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RL16 (int /*<<< orphan*/ *) ; 
 int AV_RL32 (int /*<<< orphan*/ *) ; 
 int MKTAG (char,char,char,char) ; 
 int WV_BLOCK_LIMIT ; 

__attribute__((used)) static int wv_probe(const AVProbeData *p)
{
    /* check file header */
    if (p->buf_size <= 32)
        return 0;
    if (AV_RL32(&p->buf[0]) == MKTAG('w', 'v', 'p', 'k') &&
        AV_RL32(&p->buf[4]) >= 24 &&
        AV_RL32(&p->buf[4]) <= WV_BLOCK_LIMIT &&
        AV_RL16(&p->buf[8]) >= 0x402 &&
        AV_RL16(&p->buf[8]) <= 0x410)
        return AVPROBE_SCORE_MAX;
    else
        return 0;
}