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
struct TYPE_3__ {int /*<<< orphan*/  UniStrValue; int /*<<< orphan*/  StrValue; int /*<<< orphan*/  Int64Value; int /*<<< orphan*/  IntValue; } ;
typedef  TYPE_1__ RPC_TEST ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcTest(PACK *p, RPC_TEST *t)
{
	PackAddInt(p, "IntValue", t->IntValue);
	PackAddInt64(p, "Int64Value", t->Int64Value);
	PackAddStr(p, "StrValue", t->StrValue);
	PackAddUniStr(p, "UniStrValue", t->UniStrValue);
}