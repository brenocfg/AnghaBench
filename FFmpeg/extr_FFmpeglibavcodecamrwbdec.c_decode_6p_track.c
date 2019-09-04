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

/* Variables and functions */
 int BIT_POS (int,int) ; 
 int BIT_STR (int,int,int) ; 
 int /*<<< orphan*/  decode_1p_track (int*,int,int,int) ; 
 int /*<<< orphan*/  decode_2p_track (int*,int,int,int) ; 
 int /*<<< orphan*/  decode_3p_track (int*,int,int,int) ; 
 int /*<<< orphan*/  decode_4p_track (int*,int,int,int) ; 
 int /*<<< orphan*/  decode_5p_track (int*,int,int,int) ; 

__attribute__((used)) static void decode_6p_track(int *out, int code, int m, int off) ///code: 6m-2 bits
{
    int b_offset = 1 << (m - 1);
    /* which half has more pulses in cases 0 to 2 */
    int half_more  = BIT_POS(code, 6*m - 5) << (m - 1);
    int half_other = b_offset - half_more;

    switch (BIT_STR(code, 6*m - 4, 2)) { /* case ID (2 bits) */
    case 0: /* 0 pulses in A, 6 pulses in B or vice versa */
        decode_1p_track(out, BIT_STR(code, 0, m),
                        m - 1, off + half_more);
        decode_5p_track(out + 1, BIT_STR(code, m, 5*m - 5),
                        m - 1, off + half_more);
        break;
    case 1: /* 1 pulse in A, 5 pulses in B or vice versa */
        decode_1p_track(out, BIT_STR(code, 0, m),
                        m - 1, off + half_other);
        decode_5p_track(out + 1, BIT_STR(code, m, 5*m - 5),
                        m - 1, off + half_more);
        break;
    case 2: /* 2 pulses in A, 4 pulses in B or vice versa */
        decode_2p_track(out, BIT_STR(code, 0, 2*m - 1),
                        m - 1, off + half_other);
        decode_4p_track(out + 2, BIT_STR(code, 2*m - 1, 4*m - 4),
                        m - 1, off + half_more);
        break;
    case 3: /* 3 pulses in A, 3 pulses in B */
        decode_3p_track(out, BIT_STR(code, 3*m - 2, 3*m - 2),
                        m - 1, off);
        decode_3p_track(out + 3, BIT_STR(code, 0, 3*m - 2),
                        m - 1, off + b_offset);
        break;
    }
}