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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/ * expand5 ; 
 int /*<<< orphan*/ * expand6 ; 

__attribute__((used)) static inline void rgb5652rgb(uint8_t *out, uint16_t v)
{
    int rv = (v & 0xf800) >> 11;
    int gv = (v & 0x07e0) >> 5;
    int bv = (v & 0x001f) >> 0;

    out[0] = expand5[rv];
    out[1] = expand6[gv];
    out[2] = expand5[bv];
    out[3] = 0;
}