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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int rnd () ; 
 int /*<<< orphan*/  setdx (int,int,int,int) ; 
 int /*<<< orphan*/  setdx2 (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  setpx (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void randomize_loopfilter_buffers(int lineoff, int str,
                                         int dir, int flim_E, int flim_I,
                                         int hev_thresh, uint8_t *buf,
                                         int force_hev)
{
    uint32_t mask = 0xff;
    int off = dir ? lineoff : lineoff * str;
    int istride = dir ? 1 : str;
    int jstride = dir ? str : 1;
    int i;
    for (i = 0; i < 8; i += 2) {
        // Row 0 will trigger hev for q0/q1, row 2 will trigger hev for p0/p1,
        // rows 4 and 6 will not trigger hev.
        // force_hev 1 will make sure all rows trigger hev, while force_hev -1
        // makes none of them trigger it.
        int idx = off + i * istride, p2, p1, p0, q0, q1, q2;
        setpx(idx,  0, q0 = rnd() & mask);
        if (i == 0 && force_hev >= 0 || force_hev > 0)
            setdx2(idx, 1, q1, q0, hev_thresh + 1, flim_I - hev_thresh - 1);
        else
            setdx(idx,  1, q1 = q0, hev_thresh);
        setdx(idx,  2, q2 = q1, flim_I);
        setdx(idx,  3, q2,      flim_I);
        setdx(idx, -1, p0 = q0, flim_E >> 2);
        if (i == 2 && force_hev >= 0 || force_hev > 0)
            setdx2(idx, -2, p1, p0, hev_thresh + 1, flim_I - hev_thresh - 1);
        else
            setdx(idx, -2, p1 = p0, hev_thresh);
        setdx(idx, -3, p2 = p1, flim_I);
        setdx(idx, -4, p2,      flim_I);
    }
}