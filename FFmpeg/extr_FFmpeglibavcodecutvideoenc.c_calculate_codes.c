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
typedef  int uint32_t ;
struct TYPE_4__ {int len; int code; } ;
typedef  TYPE_1__ HuffEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ff_ut_huff_cmp_len ; 
 int /*<<< orphan*/  huff_cmp_sym ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void calculate_codes(HuffEntry *he)
{
    int last, i;
    uint32_t code;

    qsort(he, 256, sizeof(*he), ff_ut_huff_cmp_len);

    last = 255;
    while (he[last].len == 255 && last)
        last--;

    code = 1;
    for (i = last; i >= 0; i--) {
        he[i].code  = code >> (32 - he[i].len);
        code       += 0x80000000u >> (he[i].len - 1);
    }

    qsort(he, 256, sizeof(*he), huff_cmp_sym);
}