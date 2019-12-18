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
typedef  int uint32_t ;

/* Variables and functions */
 int* S1 ; 
 int* S2 ; 
 int* S3 ; 
 int* S4 ; 
 int* S5 ; 
 int* S6 ; 
 int* S7 ; 
 int* S8 ; 

__attribute__((used)) static inline uint32_t
Fconf(uint32_t r0, uint32_t skl, uint32_t skr)
{
	uint32_t r1;

	r1 = (r0 << 16) | (r0 >> 16);
	return
		  S1[((r1 >> 11) ^ (skl >> 18)) & 0x3F]
		| S2[((r0 >> 23) ^ (skl >> 12)) & 0x3F]
		| S3[((r0 >> 19) ^ (skl >>  6)) & 0x3F]
		| S4[((r0 >> 15) ^ (skl      )) & 0x3F]
		| S5[((r0 >> 11) ^ (skr >> 18)) & 0x3F]
		| S6[((r0 >>  7) ^ (skr >> 12)) & 0x3F]
		| S7[((r0 >>  3) ^ (skr >>  6)) & 0x3F]
		| S8[((r1 >> 15) ^ (skr      )) & 0x3F];
}