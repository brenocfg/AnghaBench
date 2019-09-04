#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* cb_vlc; } ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ On2AVCContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  on2avc_scale (int,float) ; 
 int sign_extend (int,int) ; 

__attribute__((used)) static int on2avc_decode_quads(On2AVCContext *c, GetBitContext *gb, float *dst,
                               int dst_size, int type, float band_scale)
{
    int i, j, val, val1;

    for (i = 0; i < dst_size; i += 4) {
        val = get_vlc2(gb, c->cb_vlc[type].table, 9, 3);

        for (j = 0; j < 4; j++) {
            val1 = sign_extend((val >> (12 - j * 4)) & 0xF, 4);
            *dst++ = on2avc_scale(val1, band_scale);
        }
    }

    return 0;
}