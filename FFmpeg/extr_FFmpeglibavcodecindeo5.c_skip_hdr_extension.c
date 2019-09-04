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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int skip_hdr_extension(GetBitContext *gb)
{
    int i, len;

    do {
        len = get_bits(gb, 8);
        if (8*len > get_bits_left(gb))
            return AVERROR_INVALIDDATA;
        for (i = 0; i < len; i++) skip_bits(gb, 8);
    } while(len);

    return 0;
}