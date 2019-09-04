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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {TYPE_1__* Cedar; int /*<<< orphan*/ * Account; } ;
struct TYPE_4__ {int /*<<< orphan*/ * Client; } ;
typedef  TYPE_2__ SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  CiNotify (int /*<<< orphan*/ *) ; 

void Notify(SESSION *s, UINT code)
{
	// Validate arguments
	if (s == NULL || s->Account == NULL || s->Cedar->Client == NULL)
	{
		return;
	}

	CiNotify(s->Cedar->Client);
}