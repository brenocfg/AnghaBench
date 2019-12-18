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
typedef  size_t BYTE ;

/* Variables and functions */
 size_t* dot2_table ; 
 size_t* dot3_table ; 

void MixColumns(BYTE *in, BYTE *out)
{

    out[0] = dot2_table[in[0]] ^ dot3_table[in[1]] ^ in[2] ^ in[3];
    out[1] = in[0] ^ dot2_table[in[1]] ^ dot3_table[in[2]] ^ in[3];
    out[2] = in[0] ^ in[1] ^ dot2_table[in[2]] ^ dot3_table[in[3]];
    out[3] = dot3_table[in[0]] ^ in[1] ^ in[2] ^ dot2_table[in[3]];
}