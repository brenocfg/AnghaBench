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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_3__ {int /*<<< orphan*/  nbBits; int /*<<< orphan*/  const byte; } ;
typedef  TYPE_1__ HUFv05_DEltX2 ;
typedef  int /*<<< orphan*/  const BYTE ;
typedef  int /*<<< orphan*/  BITv05_DStream_t ;

/* Variables and functions */
 size_t BITv05_lookBitsFast (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  BITv05_skipBits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BYTE HUFv05_decodeSymbolX2(BITv05_DStream_t* Dstream, const HUFv05_DEltX2* dt, const U32 dtLog)
{
        const size_t val = BITv05_lookBitsFast(Dstream, dtLog); /* note : dtLog >= 1 */
        const BYTE c = dt[val].byte;
        BITv05_skipBits(Dstream, dt[val].nbBits);
        return c;
}