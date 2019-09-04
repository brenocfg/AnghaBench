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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  TYPE_1__ AV1OBU ;

/* Variables and functions */
 scalar_t__ AV1_OBU_FRAME ; 
 scalar_t__ AV1_OBU_FRAME_HEADER ; 
 int ff_av1_extract_obu (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int av1_parser_split(AVCodecContext *avctx,
                            const uint8_t *buf, int buf_size)
{
    AV1OBU obu;
    const uint8_t *ptr = buf, *end = buf + buf_size;

    while (ptr < end) {
        int len = ff_av1_extract_obu(&obu, ptr, buf_size, avctx);
        if (len < 0)
            break;

        if (obu.type == AV1_OBU_FRAME_HEADER ||
            obu.type == AV1_OBU_FRAME) {
            return ptr - buf;
        }
        ptr      += len;
        buf_size -= len;
    }

    return 0;
}