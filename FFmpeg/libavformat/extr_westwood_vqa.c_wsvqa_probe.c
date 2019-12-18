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
 scalar_t__ AV_RB32 (int /*<<< orphan*/ *) ; 
 scalar_t__ FORM_TAG ; 
 scalar_t__ WVQA_TAG ; 

__attribute__((used)) static int wsvqa_probe(const AVProbeData *p)
{
    /* need 12 bytes to qualify */
    if (p->buf_size < 12)
        return 0;

    /* check for the VQA signatures */
    if ((AV_RB32(&p->buf[0]) != FORM_TAG) ||
        (AV_RB32(&p->buf[8]) != WVQA_TAG))
        return 0;

    return AVPROBE_SCORE_MAX;
}