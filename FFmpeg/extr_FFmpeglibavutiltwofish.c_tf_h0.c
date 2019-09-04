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
typedef  size_t uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WL32 (size_t*,int) ; 
 size_t* q0 ; 
 size_t* q1 ; 

__attribute__((used)) static void tf_h0(uint8_t y[4], uint32_t L[4], int k)
{
    uint8_t l[4];
    if (k == 4) {
        AV_WL32(l, L[3]);
        y[0] = q1[y[0]] ^ l[0];
        y[1] = q0[y[1]] ^ l[1];
        y[2] = q0[y[2]] ^ l[2];
        y[3] = q1[y[3]] ^ l[3];
    }
    if (k >= 3) {
        AV_WL32(l, L[2]);
        y[0] = q1[y[0]] ^ l[0];
        y[1] = q1[y[1]] ^ l[1];
        y[2] = q0[y[2]] ^ l[2];
        y[3] = q0[y[3]] ^ l[3];
    }
    AV_WL32(l, L[1]);
    y[0] = q1[q0[q0[y[0]] ^ l[0]] ^ (L[0] & 0xff)];
    y[1] = q0[q0[q1[y[1]] ^ l[1]] ^ ((L[0] >> 8) & 0xff)];
    y[2] = q1[q1[q0[y[2]] ^ l[2]] ^ ((L[0] >> 16) & 0xff)];
    y[3] = q0[q1[q1[y[3]] ^ l[3]] ^ (L[0] >> 24)];
}