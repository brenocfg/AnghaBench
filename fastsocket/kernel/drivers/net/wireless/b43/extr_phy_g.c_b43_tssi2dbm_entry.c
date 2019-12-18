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
typedef  int u8 ;
typedef  int s8 ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 int EINVAL ; 
 int abs (int) ; 
 int b43_tssi2dbm_ad (int,int) ; 
 int clamp_val (int,int,int) ; 
 int max (int,int) ; 

__attribute__((used)) static s8 b43_tssi2dbm_entry(s8 entry[], u8 index,
			     s16 pab0, s16 pab1, s16 pab2)
{
	s32 m1, m2, f = 256, q, delta;
	s8 i = 0;

	m1 = b43_tssi2dbm_ad(16 * pab0 + index * pab1, 32);
	m2 = max(b43_tssi2dbm_ad(32768 + index * pab2, 256), 1);
	do {
		if (i > 15)
			return -EINVAL;
		q = b43_tssi2dbm_ad(f * 4096 -
				    b43_tssi2dbm_ad(m2 * f, 16) * f, 2048);
		delta = abs(q - f);
		f = q;
		i++;
	} while (delta >= 2);
	entry[index] = clamp_val(b43_tssi2dbm_ad(m1 * f, 8192), -127, 128);
	return 0;
}