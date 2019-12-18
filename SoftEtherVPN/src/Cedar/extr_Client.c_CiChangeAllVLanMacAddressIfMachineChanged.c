#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CiChangeAllVLanMacAddress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiGetCurrentMachineHash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiGetCurrentMachineHashNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiGetCurrentMachineHashOld (int /*<<< orphan*/ *) ; 
 int CiReadLastMachineHash (int /*<<< orphan*/ *) ; 
 int CiWriteLastMachineHash (int /*<<< orphan*/ *) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int MsIsAdmin () ; 
 int SHA1_SIZE ; 

void CiChangeAllVLanMacAddressIfMachineChanged(CLIENT *c)
{
	UCHAR current_hash_new[SHA1_SIZE];
	UCHAR current_hash[SHA1_SIZE];
	UCHAR current_hash_old[SHA1_SIZE];
	UCHAR saved_hash[SHA1_SIZE];
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

#ifdef OS_WIN32
	if (MsIsAdmin() == false)
	{
		return;
	}
#endif

	CiGetCurrentMachineHashNew(current_hash_new);
	CiGetCurrentMachineHash(current_hash);
	CiGetCurrentMachineHashOld(current_hash_old);

	if (CiReadLastMachineHash(saved_hash) == false)
	{
		CiWriteLastMachineHash(current_hash_new);
		return;
	}

	if (Cmp(saved_hash, current_hash_old, SHA1_SIZE) == 0)
	{
		CiWriteLastMachineHash(current_hash_new);
		return;
	}

	if (Cmp(saved_hash, current_hash, SHA1_SIZE) == 0)
	{
		CiWriteLastMachineHash(current_hash_new);
		return;
	}

	if (Cmp(saved_hash, current_hash_new, SHA1_SIZE) == 0)
	{
		return;
	}

	if (CiWriteLastMachineHash(current_hash_new) == false)
	{
		return;
	}

	CiChangeAllVLanMacAddress(c);
}