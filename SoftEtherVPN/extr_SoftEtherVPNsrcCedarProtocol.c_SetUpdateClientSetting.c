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
typedef  int /*<<< orphan*/  UPDATE_CLIENT_SETTING ;
struct TYPE_3__ {int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  Setting; } ;
typedef  TYPE_1__ UPDATE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 

void SetUpdateClientSetting(UPDATE_CLIENT *c, UPDATE_CLIENT_SETTING *s)
{
	// Validate arguments
	if (c == NULL || s == NULL)
	{
		return;
	}

	Copy(&c->Setting, s, sizeof(UPDATE_CLIENT_SETTING));

	Set(c->HaltEvent);
}