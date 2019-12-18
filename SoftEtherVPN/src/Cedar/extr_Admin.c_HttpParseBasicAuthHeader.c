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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  key ;
typedef  int UINT ;
struct TYPE_3__ {char* Data; } ;
typedef  TYPE_1__ HTTP_VALUE ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  Decode64 (char*,char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 TYPE_1__* GetHttpValue (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ GetKeyAndValue (char*,char*,int,char*,int,char*) ; 
 int IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrSize (char*) ; 
 char* ZeroMalloc (int) ; 

bool HttpParseBasicAuthHeader(HTTP_HEADER *h, char *username, UINT username_size, char *password, UINT password_size)
{
	bool ret = false;
	HTTP_VALUE *auth_value;
	HTTP_VALUE *vpnadmin_hubname;
	HTTP_VALUE *vpnadmin_password;
	if (h == NULL || username == NULL || password == NULL)
	{
		return false;
	}

	auth_value = GetHttpValue(h, "Authorization");
	vpnadmin_hubname = GetHttpValue(h, "X-VPNADMIN-HUBNAME");
	vpnadmin_password = GetHttpValue(h, "X-VPNADMIN-PASSWORD");

	if (vpnadmin_password != NULL)
	{
		if (vpnadmin_hubname == NULL)
		{
			StrCpy(username, username_size, "");
		}
		else
		{
			StrCpy(username, username_size, vpnadmin_hubname->Data);
		}

		StrCpy(password, password_size, vpnadmin_password->Data);

		ret = true;
	}

	if (ret == false && auth_value != NULL)
	{
		char key[32], value[MAX_SIZE];

		if (GetKeyAndValue(auth_value->Data, key, sizeof(key), value, sizeof(value), " \t"))
		{
			if (StrCmpi(key, "Basic") == 0 && IsEmptyStr(value) == false)
			{
				UINT b64_dest_size = StrSize(value) * 2 + 256;
				char *b64_dest = ZeroMalloc(b64_dest_size);

				Decode64(b64_dest, value);

				if (IsEmptyStr(b64_dest) == false)
				{
					if (b64_dest[0] == ':')
					{
						// Empty username
						StrCpy(username, username_size, "");
						StrCpy(password, password_size, b64_dest + 1);
						ret = true;
					}
					else
					{
						if (GetKeyAndValue(b64_dest, username, username_size, password, password_size, ":"))
						{
							ret = true;
						}
					}
				}

				Free(b64_dest);
			}
		}
	}

	return ret;
}