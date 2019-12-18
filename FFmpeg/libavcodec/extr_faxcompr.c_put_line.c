#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void put_line(uint8_t *dst, int size, int width, const int *runs)
{
    PutBitContext pb;
    int run, mode = ~0, pix_left = width, run_idx = 0;

    init_put_bits(&pb, dst, size);
    while (pix_left > 0) {
        run       = runs[run_idx++];
        mode      = ~mode;
        pix_left -= run;
        for (; run > 16; run -= 16)
            put_sbits(&pb, 16, mode);
        if (run)
            put_sbits(&pb, run, mode);
    }
    flush_put_bits(&pb);
}