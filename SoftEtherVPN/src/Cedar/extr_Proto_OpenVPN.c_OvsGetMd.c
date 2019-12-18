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
typedef  int /*<<< orphan*/  MD ;

/* Variables and functions */
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/ * NewMd (char*) ; 
 char* OPENVPN_DEFAULT_MD ; 

MD *OvsGetMd(char *name)
{
	MD *m = NULL;

	if (IsEmptyStr(name) == false)
	{
		m = NewMd(name);
	}

	if (m == NULL)
	{
		m = NewMd(OPENVPN_DEFAULT_MD);
	}

	return m;
}