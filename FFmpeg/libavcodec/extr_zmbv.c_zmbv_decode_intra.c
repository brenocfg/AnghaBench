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
struct TYPE_3__ {scalar_t__ fmt; int width; int height; int bpp; int /*<<< orphan*/  cur; int /*<<< orphan*/  pal; int /*<<< orphan*/ * decomp_buf; } ;
typedef  TYPE_1__ ZmbvContext ;

/* Variables and functions */
 scalar_t__ ZMBV_FMT_8BPP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int zmbv_decode_intra(ZmbvContext *c)
{
    uint8_t *src = c->decomp_buf;

    /* make the palette available on the way out */
    if (c->fmt == ZMBV_FMT_8BPP) {
        memcpy(c->pal, src, 768);
        src += 768;
    }

    memcpy(c->cur, src, c->width * c->height * (c->bpp / 8));
    return 0;
}