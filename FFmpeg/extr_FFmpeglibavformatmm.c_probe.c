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
struct TYPE_3__ {scalar_t__ buf_size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RL16 (int /*<<< orphan*/ *) ; 
 int AV_RL32 (int /*<<< orphan*/ *) ; 
 int MM_HEADER_LEN_AV ; 
 int MM_HEADER_LEN_V ; 
 scalar_t__ MM_PREAMBLE_SIZE ; 
 int MM_TYPE_HEADER ; 

__attribute__((used)) static int probe(const AVProbeData *p)
{
    int len, type, fps, w, h;
    if (p->buf_size < MM_HEADER_LEN_AV + MM_PREAMBLE_SIZE)
        return 0;
    /* the first chunk is always the header */
    if (AV_RL16(&p->buf[0]) != MM_TYPE_HEADER)
        return 0;
    len = AV_RL32(&p->buf[2]);
    if (len != MM_HEADER_LEN_V && len != MM_HEADER_LEN_AV)
        return 0;
    fps = AV_RL16(&p->buf[8]);
    w = AV_RL16(&p->buf[12]);
    h = AV_RL16(&p->buf[14]);
    if (!fps || fps > 60 || !w || w > 2048 || !h || h > 2048)
        return 0;
    type = AV_RL16(&p->buf[len]);
    if (!type || type > 0x31)
        return 0;

    /* only return half certainty since this check is a bit sketchy */
    return AVPROBE_SCORE_EXTENSION;
}