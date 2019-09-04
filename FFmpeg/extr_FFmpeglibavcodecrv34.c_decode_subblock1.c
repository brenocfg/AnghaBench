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
typedef  int /*<<< orphan*/  VLC ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  decode_coeff (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int* modulo_three_table ; 

__attribute__((used)) static inline void decode_subblock1(int16_t *dst, int code, GetBitContext *gb, VLC *vlc, int q)
{
    int coeff = modulo_three_table[code] >> 6;
    decode_coeff(dst, coeff, 3, gb, vlc, q);
}