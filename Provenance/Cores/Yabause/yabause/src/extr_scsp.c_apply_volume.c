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
typedef  int u32 ;
typedef  int u16 ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */

s16 apply_volume(u16 tl, u16 slot_att, const s16 s)
{
   u32 tl_att = tl * 4;
   u32 att_clipped = 0;
   s32 sample_att = 0;
   u32 shift = 0;

   tl_att += slot_att;

   att_clipped = tl_att;
   att_clipped &= 0x3f;
   att_clipped ^= 0x7f;
   att_clipped += 1;

   sample_att = s * att_clipped;
   shift = tl_att >> 6;

   sample_att = sample_att >> (shift + 7);

   return sample_att;
}