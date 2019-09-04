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
typedef  float int16_t ;
typedef  enum Mode { ____Placeholder_Mode } Mode ;

/* Variables and functions */
 int const MODE_8k85 ; 
 float** qua_gain_6b ; 
 float** qua_gain_7b ; 

__attribute__((used)) static void decode_gains(const uint8_t vq_gain, const enum Mode mode,
                         float *fixed_gain_factor, float *pitch_gain)
{
    const int16_t *gains = (mode <= MODE_8k85 ? qua_gain_6b[vq_gain] :
                                                qua_gain_7b[vq_gain]);

    *pitch_gain        = gains[0] * (1.0f / (1 << 14));
    *fixed_gain_factor = gains[1] * (1.0f / (1 << 11));
}