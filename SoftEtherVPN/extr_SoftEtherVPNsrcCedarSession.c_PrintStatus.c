#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_8__ {TYPE_2__* Account; TYPE_1__* Cedar; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* StatusPrinter ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int /*<<< orphan*/ * Client; } ;
typedef  TYPE_3__ SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

void PrintStatus(SESSION *s, wchar_t *str)
{
	// Validate arguments
	if (s == NULL || str == NULL || s->Account == NULL || s->Cedar->Client == NULL
		|| s->Account->StatusPrinter == NULL)
	{
		return;
	}

	// Inform the status to the callback function
	s->Account->StatusPrinter(s, str);
}