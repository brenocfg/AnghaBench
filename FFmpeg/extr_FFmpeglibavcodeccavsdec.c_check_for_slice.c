#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mb_height; int /*<<< orphan*/  stc; scalar_t__ mbx; int /*<<< orphan*/  gb; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AVSContext ;

/* Variables and functions */
 int /*<<< orphan*/  decode_slice_header (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 
 int show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int check_for_slice(AVSContext *h)
{
    GetBitContext *gb = &h->gb;
    int align;

    if (h->mbx)
        return 0;
    align = (-get_bits_count(gb)) & 7;
    /* check for stuffing byte */
    if (!align && (show_bits(gb, 8) == 0x80))
        align = 8;
    if ((show_bits_long(gb, 24 + align) & 0xFFFFFF) == 0x000001) {
        skip_bits_long(gb, 24 + align);
        h->stc = get_bits(gb, 8);
        if (h->stc >= h->mb_height)
            return 0;
        decode_slice_header(h, gb);
        return 1;
    }
    return 0;
}