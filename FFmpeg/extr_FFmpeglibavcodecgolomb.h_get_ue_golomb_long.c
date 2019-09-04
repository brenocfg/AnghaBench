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
 int av_log2 (unsigned int) ; 
 int get_bits_long (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline unsigned get_ue_golomb_long(GetBitContext *gb)
{
    unsigned buf, log;

    buf = show_bits_long(gb, 32);
    log = 31 - av_log2(buf);
    skip_bits_long(gb, log);

    return get_bits_long(gb, log + 1) - 1;
}