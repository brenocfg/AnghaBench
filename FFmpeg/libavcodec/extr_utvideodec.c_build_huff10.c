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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  VLC ;
struct TYPE_3__ {int sym; int len; } ;
typedef  TYPE_1__ HuffEntry ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_BITS ; 
 int ff_init_vlc_sparse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int,int,int*,int,int,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_ut10_huff_cmp_len ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_huff10(const uint8_t *src, VLC *vlc, int *fsym)
{
    int i;
    HuffEntry he[1024];
    int last;
    uint32_t codes[1024];
    uint8_t bits[1024];
    uint16_t syms[1024];
    uint32_t code;

    *fsym = -1;
    for (i = 0; i < 1024; i++) {
        he[i].sym = i;
        he[i].len = *src++;
    }
    qsort(he, 1024, sizeof(*he), ff_ut10_huff_cmp_len);

    if (!he[0].len) {
        *fsym = he[0].sym;
        return 0;
    }

    last = 1023;
    while (he[last].len == 255 && last)
        last--;

    if (he[last].len > 32) {
        return -1;
    }

    code = 1;
    for (i = last; i >= 0; i--) {
        codes[i] = code >> (32 - he[i].len);
        bits[i]  = he[i].len;
        syms[i]  = he[i].sym;
        code += 0x80000000u >> (he[i].len - 1);
    }
#define VLC_BITS 11
    return ff_init_vlc_sparse(vlc, VLC_BITS, last + 1,
                              bits,  sizeof(*bits),  sizeof(*bits),
                              codes, sizeof(*codes), sizeof(*codes),
                              syms,  sizeof(*syms),  sizeof(*syms), 0);
}