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
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ buf_size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ HEADER_SIZE ; 
 scalar_t__ MKTAG (char,char,char,int /*<<< orphan*/ ) ; 
 scalar_t__ bytestream_get_le16 (int /*<<< orphan*/  const**) ; 
 scalar_t__ bytestream_get_le32 (int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int msnwc_tcp_probe(const AVProbeData *p)
{
    int i;

    for (i = 0; i + HEADER_SIZE <= p->buf_size; i++) {
        uint16_t width, height;
        uint32_t fourcc;
        const uint8_t *bytestream = p->buf + i;

        if (bytestream_get_le16(&bytestream) != HEADER_SIZE)
            continue;
        width  = bytestream_get_le16(&bytestream);
        height = bytestream_get_le16(&bytestream);
        if (!(width == 320 &&
              height == 240) && !(width == 160 && height == 120))
            continue;
        bytestream += 2; // keyframe
        bytestream += 4; // size
        fourcc      = bytestream_get_le32(&bytestream);
        if (fourcc != MKTAG('M', 'L', '2', '0'))
            continue;

        if (i) {
            if (i < 14) /* starts with SwitchBoard connection info */
                return AVPROBE_SCORE_MAX / 2;
            else        /* starts in the middle of stream */
                return AVPROBE_SCORE_MAX / 3;
        } else {
            return AVPROBE_SCORE_MAX;
        }
    }

    return 0;
}