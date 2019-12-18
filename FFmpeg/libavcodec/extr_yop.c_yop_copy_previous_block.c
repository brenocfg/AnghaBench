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
typedef  void* uint8_t ;
struct TYPE_3__ {void** dstptr; void** dstbuf; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ YopDecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int** motion_vector ; 

__attribute__((used)) static int yop_copy_previous_block(YopDecContext *s, int linesize, int copy_tag)
{
    uint8_t *bufptr;

    // Calculate position for the copy source
    bufptr = s->dstptr + motion_vector[copy_tag][0] +
             linesize * motion_vector[copy_tag][1];
    if (bufptr < s->dstbuf) {
        av_log(s->avctx, AV_LOG_ERROR, "File probably corrupt\n");
        return AVERROR_INVALIDDATA;
    }

    s->dstptr[0]            = bufptr[0];
    s->dstptr[1]            = bufptr[1];
    s->dstptr[linesize]     = bufptr[linesize];
    s->dstptr[linesize + 1] = bufptr[linesize + 1];

    return 0;
}