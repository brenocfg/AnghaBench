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
 int MAX_UINT_BITS (int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cbs_h2645_read_more_rbsp_data(GetBitContext *gbc)
{
    int bits_left = get_bits_left(gbc);
    if (bits_left > 8)
        return 1;
    if (bits_left == 0)
        return 0;
    if (show_bits(gbc, bits_left) & MAX_UINT_BITS(bits_left - 1))
        return 1;
    return 0;
}