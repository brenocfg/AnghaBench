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
struct TYPE_4__ {int /*<<< orphan*/  CommonProxySetting; } ;
typedef  int /*<<< orphan*/  INTERNET_SETTING ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_1__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

bool CtSetCommonProxySetting(CLIENT *c, INTERNET_SETTING *a)
{
	// Validate arguments
	if (c == NULL || a == NULL)
	{
		return false;
	}

	Copy(&c->CommonProxySetting, a, sizeof(INTERNET_SETTING));


	CiSaveConfigurationFile(c);

	return true;
}