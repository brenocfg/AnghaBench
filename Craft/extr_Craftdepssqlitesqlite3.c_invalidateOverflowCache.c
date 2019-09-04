#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ aOverflow; } ;
typedef  TYPE_1__ BtCursor ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursorHoldsMutex (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 

__attribute__((used)) static void invalidateOverflowCache(BtCursor *pCur){
  assert( cursorHoldsMutex(pCur) );
  sqlite3_free(pCur->aOverflow);
  pCur->aOverflow = 0;
}