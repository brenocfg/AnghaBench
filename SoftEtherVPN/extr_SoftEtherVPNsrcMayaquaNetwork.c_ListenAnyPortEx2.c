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
typedef  int UINT ;
typedef  int /*<<< orphan*/  SOCK ;

/* Variables and functions */
 int /*<<< orphan*/ * ListenEx (int,int) ; 

SOCK *ListenAnyPortEx2(bool local_only, bool disable_ca)
{
	UINT i;
	SOCK *s;
	for (i = 40000;i < 65536;i++)
	{
		s = ListenEx(i, local_only);
		if (s != NULL)
		{
			return s;
		}
	}

	return NULL;
}