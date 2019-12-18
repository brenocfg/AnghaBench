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
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct TYPE_5__ {int nb_symbols; int* simple_symbols; TYPE_1__ vlc; scalar_t__ simple; } ;
typedef  TYPE_2__ HuffReader ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 size_t get_bits1 (int /*<<< orphan*/ *) ; 
 int webp_get_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int huff_reader_get_symbol(HuffReader *r, GetBitContext *gb)
{
    if (r->simple) {
        if (r->nb_symbols == 1)
            return r->simple_symbols[0];
        else
            return r->simple_symbols[get_bits1(gb)];
    } else
        return webp_get_vlc(gb, r->vlc.table);
}