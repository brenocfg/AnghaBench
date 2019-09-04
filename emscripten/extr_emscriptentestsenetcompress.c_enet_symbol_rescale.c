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
typedef  int enet_uint16 ;
struct TYPE_3__ {int count; int under; int left; int /*<<< orphan*/  right; } ;
typedef  TYPE_1__ ENetSymbol ;

/* Variables and functions */

__attribute__((used)) static enet_uint16
enet_symbol_rescale (ENetSymbol * symbol)
{
    enet_uint16 total = 0;
    for (;;)
    {
        symbol -> count -= symbol->count >> 1;
        symbol -> under = symbol -> count;
        if (symbol -> left)
          symbol -> under += enet_symbol_rescale (symbol + symbol -> left);
        total += symbol -> under;
        if (! symbol -> right) break;
        symbol += symbol -> right;
    } 
    return total;
}