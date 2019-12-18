#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_5__ {size_t state; scalar_t__ table; } ;
struct TYPE_4__ {size_t newState; int /*<<< orphan*/  symbol; int /*<<< orphan*/  nbBits; } ;
typedef  TYPE_1__ FSE_decode_t ;
typedef  int /*<<< orphan*/  FSE_DStream_t ;
typedef  TYPE_2__ FSE_DState_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t FSE_readBitsFast (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static BYTE FSE_decodeSymbolFast(FSE_DState_t* DStatePtr, FSE_DStream_t* bitD)
{
    const FSE_decode_t DInfo = ((const FSE_decode_t*)(DStatePtr->table))[DStatePtr->state];
    const U32 nbBits = DInfo.nbBits;
    BYTE symbol = DInfo.symbol;
    size_t lowBits = FSE_readBitsFast(bitD, nbBits);

    DStatePtr->state = DInfo.newState + lowBits;
    return symbol;
}