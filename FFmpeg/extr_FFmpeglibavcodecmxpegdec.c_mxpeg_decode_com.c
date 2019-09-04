#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  gb; } ;
struct TYPE_6__ {TYPE_1__ jpg; } ;
typedef  TYPE_2__ MXpegDecodeContext ;

/* Variables and functions */
 int AV_RB16 (int /*<<< orphan*/  const*) ; 
 int FFMIN (int,int) ; 
 int mxpeg_decode_mxm (TYPE_2__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/  const*,char*,int) ; 

__attribute__((used)) static int mxpeg_decode_com(MXpegDecodeContext *s,
                            const uint8_t *buf_ptr, int buf_size)
{
    int len, ret = 0;
    if (buf_size < 2)
        return 0;
    len = AV_RB16(buf_ptr);
    if (len > 14 && len <= buf_size && !strncmp(buf_ptr + 2, "MXM", 3)) {
        ret = mxpeg_decode_mxm(s, buf_ptr + 2, len - 2);
    }
    skip_bits(&s->jpg.gb, 8*FFMIN(len,buf_size));

    return ret;
}