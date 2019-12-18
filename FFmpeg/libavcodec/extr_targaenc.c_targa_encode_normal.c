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
struct TYPE_3__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int targa_encode_normal(uint8_t *outbuf, const AVFrame *pic, int bpp, int w, int h)
{
    int i, n = bpp * w;
    uint8_t *out = outbuf;
    uint8_t *ptr = pic->data[0];

    for(i=0; i < h; i++) {
        memcpy(out, ptr, n);
        out += n;
        ptr += pic->linesize[0];
    }

    return out - outbuf;
}