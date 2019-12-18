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
struct TYPE_3__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ VLC ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FF_ARRAY_ELEMS (int*) ; 
 int* code_prefix ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_bitsz (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qdmc_get_vlc(GetBitContext *gb, VLC *table, int flag)
{
    int v;

    if (get_bits_left(gb) < 1)
        return AVERROR_INVALIDDATA;
    v = get_vlc2(gb, table->table, table->bits, 1);
    if (v < 0)
        return AVERROR_INVALIDDATA;
    if (v)
        v = v - 1;
    else
        v = get_bits(gb, get_bits(gb, 3) + 1);

    if (flag) {
        if (v >= FF_ARRAY_ELEMS(code_prefix))
            return AVERROR_INVALIDDATA;

        v = code_prefix[v] + get_bitsz(gb, v >> 2);
    }

    return v;
}