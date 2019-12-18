#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_3__ {int* excitation; } ;
typedef  TYPE_1__ DssSpContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int*) ; 
 int SUBFRAMES ; 
 int av_clip_int16 (int) ; 
 int* dss_sp_sinc ; 

__attribute__((used)) static void dss_sp_update_state(DssSpContext *p, int32_t *dst)
{
    int i, offset = 6, counter = 0, a = 0;

    for (i = 0; i < 6; i++)
        p->excitation[i] = p->excitation[288 + i];

    for (i = 0; i < 72 * SUBFRAMES; i++)
        p->excitation[6 + i] = dst[i];

    do {
        int tmp = 0;

        for (i = 0; i < 6; i++)
            tmp += p->excitation[offset--] * dss_sp_sinc[a + i * 11];

        offset += 7;

        tmp >>= 15;
        dst[counter] = av_clip_int16(tmp);

        counter++;

        a = (a + 1) % 11;
        if (!a)
            offset++;
    } while (offset < FF_ARRAY_ELEMS(p->excitation));
}