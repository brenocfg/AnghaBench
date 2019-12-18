#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;
struct TYPE_3__ {scalar_t__ m68k_address; int native_offset; } ;

/* Variables and functions */
 TYPE_1__* btcache ; 
 int btcache_index ; 
 int lenof (TYPE_1__*) ; 

__attribute__((used)) static int32_t btcache_lookup(uint32_t address)
{
    /* Search backwards from the current instruction so we can handle short
     * loops quickly; note that btcache_index is now pointing to where the
     * _next_ instruction will go */
    const int current = (btcache_index + (lenof(btcache)-1)) % lenof(btcache);
    int index = current;
    do {
        if (btcache[index].m68k_address == address) {
            return btcache[index].native_offset;
        }
        index = (index + (lenof(btcache)-1)) % lenof(btcache);
    } while (index != current);
    return -1;
}