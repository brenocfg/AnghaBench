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
typedef  int /*<<< orphan*/  WalIndexHdr ;
typedef  int /*<<< orphan*/  WalCkptInfo ;
struct TYPE_3__ {scalar_t__ nWiData; int /*<<< orphan*/ ** apWiData; } ;
typedef  TYPE_1__ Wal ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static volatile WalCkptInfo *walCkptInfo(Wal *pWal){
  assert( pWal->nWiData>0 && pWal->apWiData[0] );
  return (volatile WalCkptInfo*)&(pWal->apWiData[0][sizeof(WalIndexHdr)/2]);
}