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
typedef  int int16_t ;
struct TYPE_4__ {int* permutated; } ;
struct TYPE_5__ {int* last_dc; int* block_last_index; TYPE_1__ intra_scantable; int /*<<< orphan*/ * mjpeg_ctx; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  int /*<<< orphan*/  MJpegContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_mjpeg_encode_code (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ff_mjpeg_encode_coef (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void record_block(MpegEncContext *s, int16_t *block, int n)
{
    int i, j, table_id;
    int component, dc, last_index, val, run;
    MJpegContext *m = s->mjpeg_ctx;

    /* DC coef */
    component = (n <= 3 ? 0 : (n&1) + 1);
    table_id = (n <= 3 ? 0 : 1);
    dc = block[0]; /* overflow is impossible */
    val = dc - s->last_dc[component];

    ff_mjpeg_encode_coef(m, table_id, val, 0);

    s->last_dc[component] = dc;

    /* AC coefs */

    run = 0;
    last_index = s->block_last_index[n];
    table_id |= 2;

    for(i=1;i<=last_index;i++) {
        j = s->intra_scantable.permutated[i];
        val = block[j];

        if (val == 0) {
            run++;
        } else {
            while (run >= 16) {
                ff_mjpeg_encode_code(m, table_id, 0xf0);
                run -= 16;
            }
            ff_mjpeg_encode_coef(m, table_id, val, run);
            run = 0;
        }
    }

    /* output EOB only if not already 64 values */
    if (last_index < 63 || run != 0)
        ff_mjpeg_encode_code(m, table_id, 0);
}