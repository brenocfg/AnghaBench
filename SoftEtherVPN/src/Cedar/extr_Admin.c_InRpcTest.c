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
struct TYPE_4__ {int /*<<< orphan*/  UniStrValue; int /*<<< orphan*/  StrValue; int /*<<< orphan*/  Int64Value; int /*<<< orphan*/  IntValue; } ;
typedef  TYPE_1__ RPC_TEST ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcTest(RPC_TEST *t, PACK *p)
{
	Zero(t, sizeof(RPC_TEST));
	t->IntValue = PackGetInt(p, "IntValue");
	t->Int64Value = PackGetInt64(p, "Int64Value");
	PackGetStr(p, "StrValue", t->StrValue, sizeof(t->StrValue));
	PackGetUniStr(p, "UniStrValue", t->UniStrValue, sizeof(t->UniStrValue));
}