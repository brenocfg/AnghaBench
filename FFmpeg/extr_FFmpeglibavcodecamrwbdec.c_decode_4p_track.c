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

__attribute__((used)) static void decode_4p_track(int *out, int code, int m, int off) ///code: 4m bits
{
    int half_4p, subhalf_2p;
    int b_offset = 1 << (m - 1);

    switch (BIT_STR(code, 4*m - 2, 2)) { /* case ID (2 bits) */
    case 0: /* 0 pulses in A, 4 pulses in B or vice versa */
        half_4p = BIT_POS(code, 4*m - 3) << (m - 1); // which has 4 pulses
        subhalf_2p = BIT_POS(code, 2*m - 3) << (m - 2);

        decode_2p_track(out, BIT_STR(code, 0, 2*m - 3),
                        m - 2, off + half_4p + subhalf_2p);
        decode_2p_track(out + 2, BIT_STR(code, 2*m - 2, 2*m - 1),
                        m - 1, off + half_4p);
        break;
    case 1: /* 1 pulse in A, 3 pulses in B */
        decode_1p_track(out, BIT_STR(code,  3*m - 2, m),
                        m - 1, off);
        decode_3p_track(out + 1, BIT_STR(code, 0, 3*m - 2),
                        m - 1, off + b_offset);
        break;
    case 2: /* 2 pulses in each half */
        decode_2p_track(out, BIT_STR(code, 2*m - 1, 2*m - 1),
                        m - 1, off);
        decode_2p_track(out + 2, BIT_STR(code, 0, 2*m - 1),
                        m - 1, off + b_offset);
        break;
    case 3: /* 3 pulses in A, 1 pulse in B */
        decode_3p_track(out, BIT_STR(code, m, 3*m - 2),
                        m - 1, off);
        decode_1p_track(out + 3, BIT_STR(code, 0, m),
                        m - 1, off + b_offset);
        break;
    }
}