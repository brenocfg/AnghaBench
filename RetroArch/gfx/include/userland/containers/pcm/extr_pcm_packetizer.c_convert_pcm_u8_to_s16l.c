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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static void convert_pcm_u8_to_s16l( uint8_t **p_out, uint8_t *in, size_t size)
{
   int16_t *out = (int16_t *)*p_out;
   uint8_t tmp;

   while(size--)
   {
      tmp = *in++;
      *out++ = ((tmp - 128) << 8) | tmp;
   }
   *p_out = (uint8_t *)out;
}