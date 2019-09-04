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
typedef  int zbar_symbol_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int _zbar_get_symbol_hash (zbar_symbol_type_t sym)
{
    static const signed char hash[0x20] = {
        0x00, 0x01, 0x10, 0x11,   -1, 0x11, 0x16, 0x0c,
	0x05, 0x06, 0x08,   -1, 0x04, 0x03, 0x07, 0x12,
	  -1,   -1,   -1,   -1,   -1,   -1,   -1, 0x02,
	  -1, 0x00, 0x12, 0x0c, 0x0b, 0x1d, 0x0a, 0x00,
     };
    int g0 = hash[sym & 0x1f];
    int g1 = hash[~(sym >> 4) & 0x1f];
    assert(g0 >= 0 && g1 >= 0);
    if(g0 < 0 || g1 < 0)
        return(0);
    return((g0 + g1) & 0x1f);
}