#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size_in_bits; } ;
typedef  TYPE_1__ GetBitContext ;

/* Variables and functions */
 int get_bits_count (TYPE_1__*) ; 
 int /*<<< orphan*/  skip_bits_long (TYPE_1__*,int) ; 

__attribute__((used)) static inline int ff_dca_seek_bits(GetBitContext *s, int p)
{
    if (p < get_bits_count(s) || p > s->size_in_bits)
        return -1;
    skip_bits_long(s, p - get_bits_count(s));
    return 0;
}