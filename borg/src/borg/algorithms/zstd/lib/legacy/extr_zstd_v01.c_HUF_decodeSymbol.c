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
typedef  TYPE_1__ HUF_DElt ;
typedef  int /*<<< orphan*/  FSE_DStream_t ;
typedef  int /*<<< orphan*/  const BYTE ;

/* Variables and functions */
 size_t FSE_lookBitsFast (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  FSE_skipBits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BYTE HUF_decodeSymbol(FSE_DStream_t* Dstream, const HUF_DElt* dt, const U32 dtLog)
{
        const size_t val = FSE_lookBitsFast(Dstream, dtLog); /* note : dtLog >= 1 */
        const BYTE c = dt[val].byte;
        FSE_skipBits(Dstream, dt[val].nbBits);
        return c;
}