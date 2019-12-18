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
typedef  int int16_t ;

/* Variables and functions */
 int FRAME_LEN ; 
 int PITCH_MAX ; 
 int /*<<< orphan*/  av_memcpy_backptr (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void residual_interp(int16_t *buf, int16_t *out, int lag,
                            int gain, int *rseed)
{
    int i;
    if (lag) { /* Voiced */
        int16_t *vector_ptr = buf + PITCH_MAX;
        /* Attenuate */
        for (i = 0; i < lag; i++)
            out[i] = vector_ptr[i - lag] * 3 >> 2;
        av_memcpy_backptr((uint8_t*)(out + lag), lag * sizeof(*out),
                          (FRAME_LEN - lag) * sizeof(*out));
    } else {  /* Unvoiced */
        for (i = 0; i < FRAME_LEN; i++) {
            *rseed = (int16_t)(*rseed * 521 + 259);
            out[i] = gain * *rseed >> 15;
        }
        memset(buf, 0, (FRAME_LEN + PITCH_MAX) * sizeof(*buf));
    }
}