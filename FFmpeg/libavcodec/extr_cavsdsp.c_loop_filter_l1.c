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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int P0 ; 
 int P1 ; 
 int P2 ; 
 int Q0 ; 
 int Q1 ; 
 int Q2 ; 
 int abs (int) ; 
 int av_clip (int,int,int) ; 
 int av_clip_uint8 (int) ; 

__attribute__((used)) static inline void loop_filter_l1(uint8_t *p0_p, ptrdiff_t stride, int alpha, int beta, int tc)
{
    int p0 = P0;
    int q0 = Q0;

    if(abs(p0-q0)<alpha && abs(P1-p0)<beta && abs(Q1-q0)<beta) {
        int delta = av_clip(((q0-p0)*3+P1-Q1+4)>>3,-tc, tc);
        P0 = av_clip_uint8(p0+delta);
        Q0 = av_clip_uint8(q0-delta);
        if(abs(P2-p0)<beta) {
            delta = av_clip(((P0-P1)*3+P2-Q0+4)>>3, -tc, tc);
            P1 = av_clip_uint8(P1+delta);
        }
        if(abs(Q2-q0)<beta) {
            delta = av_clip(((Q1-Q0)*3+P0-Q2+4)>>3, -tc, tc);
            Q1 = av_clip_uint8(Q1-delta);
        }
    }
}