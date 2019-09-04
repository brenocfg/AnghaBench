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
struct TYPE_5__ {int /*<<< orphan*/  gb; int /*<<< orphan*/  last_resync_gb; } ;
struct TYPE_6__ {scalar_t__ gob_start_code_skipped; TYPE_1__ s; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ H261Context ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int h261_decode_gob_header (TYPE_2__*) ; 
 scalar_t__ show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int h261_resync(H261Context *h)
{
    MpegEncContext *const s = &h->s;
    int left, ret;

    if (h->gob_start_code_skipped) {
        ret = h261_decode_gob_header(h);
        if (ret >= 0)
            return 0;
    } else {
        if (show_bits(&s->gb, 15) == 0) {
            ret = h261_decode_gob_header(h);
            if (ret >= 0)
                return 0;
        }
        // OK, it is not where it is supposed to be ...
        s->gb = s->last_resync_gb;
        align_get_bits(&s->gb);
        left = get_bits_left(&s->gb);

        for (; left > 15 + 1 + 4 + 5; left -= 8) {
            if (show_bits(&s->gb, 15) == 0) {
                GetBitContext bak = s->gb;

                ret = h261_decode_gob_header(h);
                if (ret >= 0)
                    return 0;

                s->gb = bak;
            }
            skip_bits(&s->gb, 8);
        }
    }

    return -1;
}