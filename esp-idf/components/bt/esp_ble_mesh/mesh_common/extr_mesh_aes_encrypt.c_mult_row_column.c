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

/* Variables and functions */
 int const _double_byte (int const) ; 
 int const triple (int const) ; 

__attribute__((used)) static inline void mult_row_column(uint8_t *out, const uint8_t *in)
{
    out[0] = _double_byte(in[0]) ^ triple(in[1]) ^ in[2] ^ in[3];
    out[1] = in[0] ^ _double_byte(in[1]) ^ triple(in[2]) ^ in[3];
    out[2] = in[0] ^ in[1] ^ _double_byte(in[2]) ^ triple(in[3]);
    out[3] = triple(in[0]) ^ in[1] ^ in[2] ^ _double_byte(in[3]);
}