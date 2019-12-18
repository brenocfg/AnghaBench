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
struct TYPE_5__ {int /*<<< orphan*/  table; TYPE_1__* pTabSchema; } ;
typedef  TYPE_2__ Trigger ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_4__ {int /*<<< orphan*/  tblHash; } ;

/* Variables and functions */
 int /*<<< orphan*/ * sqlite3HashFind (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sqlite3Strlen30 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Table *tableOfTrigger(Trigger *pTrigger){
  int n = sqlite3Strlen30(pTrigger->table);
  return sqlite3HashFind(&pTrigger->pTabSchema->tblHash, pTrigger->table, n);
}