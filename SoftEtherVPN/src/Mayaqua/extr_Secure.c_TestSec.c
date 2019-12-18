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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  pin ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  Id; } ;
typedef  TYPE_1__ SECURE_DEVICE ;
typedef  int /*<<< orphan*/  SECURE ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CloseSec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseSecSession (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLine (char*,int) ; 
 int /*<<< orphan*/ * GetSecureDeviceList () ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ LoginSec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LogoutSec (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * OpenSec (scalar_t__) ; 
 int OpenSecSession (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Print (char*,...) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  TestSecMain (int /*<<< orphan*/ *) ; 
 scalar_t__ ToInt (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

void TestSec()
{
	UINT i;
	LIST *secure_device_list;
	Print("Secure Device Test Program\n"
		"Copyright (c) SoftEther Corporation. All Rights Reserved.\n\n");

	// Get the secure device list
	secure_device_list = GetSecureDeviceList();
	if (secure_device_list != NULL)
	{
		UINT use_device_id;
		char tmp[MAX_SIZE];
		Print("--- Secure Device List ---\n");
		for (i = 0;i < LIST_NUM(secure_device_list);i++)
		{
			SECURE_DEVICE *dev = LIST_DATA(secure_device_list, i);
			Print("%2u - %s\n", dev->Id, dev->DeviceName);
		}
		Print("\n");
		Print("Device ID >");
		GetLine(tmp, sizeof(tmp));
		use_device_id = ToInt(tmp);
		if (use_device_id == 0)
		{
			Print("Canceled.\n");
		}
		else
		{
			SECURE *sec = OpenSec(use_device_id);
			Print("Opening Device...\n");
			if (sec == NULL)
			{
				Print("OpenSec() Failed.\n");
			}
			else
			{
				Print("Opening Session...\n");
				if (OpenSecSession(sec, 0) == false)
				{
					Print("OpenSecSession() Failed.\n");
				}
				else
				{
					while (true)
					{
						char pin[MAX_SIZE];
						Print("PIN Code >");
						GetLine(pin, sizeof(pin));
						Trim(pin);
						if (StrLen(pin) == 0)
						{
							Print("Canceled.\n");
							break;
						}
						else
						{
							Print("Login...\n");
							if (LoginSec(sec, pin))
							{
								TestSecMain(sec);
								Print("Logout...\n");
								LogoutSec(sec);
								break;
							}
							else
							{
								Print("Login Failed. Please Try Again.\n");
							}
						}
					}
					Print("Closing Session...\n");
					CloseSecSession(sec);
				}
				Print("Closing Device...\n");
				CloseSec(sec);
			}
		}
		ReleaseList(secure_device_list);
	}
	else
	{
		Print("GetSecureDeviceList() Error.\n");
	}
}