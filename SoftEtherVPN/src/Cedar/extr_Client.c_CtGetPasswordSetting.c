#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  PasswordRemoteOnly; int /*<<< orphan*/  EncryptedPassword; } ;
struct TYPE_5__ {int IsPasswordPresented; int /*<<< orphan*/  PasswordRemoteOnly; } ;
typedef  TYPE_1__ RPC_CLIENT_PASSWORD_SETTING ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

bool CtGetPasswordSetting(CLIENT *c, RPC_CLIENT_PASSWORD_SETTING *a)
{
	UCHAR hash[SHA1_SIZE];
	// Validate arguments
	if (c == NULL || a == NULL)
	{
		return false;
	}

	Sha0(hash, "", 0);
	if (Cmp(hash, c->EncryptedPassword, SHA1_SIZE) == 0)
	{
		a->IsPasswordPresented = false;
	}
	else
	{
		a->IsPasswordPresented = true;
	}

	a->PasswordRemoteOnly = c->PasswordRemoteOnly;

	return true;
}