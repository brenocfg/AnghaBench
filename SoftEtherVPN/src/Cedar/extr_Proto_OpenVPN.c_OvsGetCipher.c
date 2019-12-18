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
typedef  int /*<<< orphan*/  lowercase_name ;
typedef  int /*<<< orphan*/  CIPHER ;

/* Variables and functions */
 int IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewCipher (char*) ; 
 char* OPENVPN_DEFAULT_CIPHER ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrLower (char*) ; 

CIPHER *OvsGetCipher(char *name)
{
	CIPHER *c = NULL;

	// OpenVPN sends the cipher name in uppercase, even if it's not standard,
	// thus we have to convert it to lowercase for EVP_get_cipherbyname().
	char lowercase_name[MAX_SIZE];
	StrCpy(lowercase_name, sizeof(lowercase_name), name);
	StrLower(lowercase_name);

	if (IsEmptyStr(lowercase_name) == false)
	{
		c = NewCipher(lowercase_name);
	}

	if (c == NULL)
	{
		c = NewCipher(OPENVPN_DEFAULT_CIPHER);
	}

	return c;
}