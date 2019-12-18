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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static void planarize_s16(int16_t *out, const int16_t *in, size_t frames)
{
   size_t i;

   for (i = 0; i < frames; i++)
   {
      out[i] = in[2 * i + 0];
      out[i + frames] = in[2 * i + 1];
   }
}