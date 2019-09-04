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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  IntValue; int /*<<< orphan*/  StrValue; } ;
typedef  TYPE_1__ RPC_TEST ;
typedef  int /*<<< orphan*/  ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  Format (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

UINT StTest(ADMIN *a, RPC_TEST *t)
{
	Format(t->StrValue, sizeof(t->StrValue), "%u", t->IntValue);

	return ERR_NO_ERROR;
}