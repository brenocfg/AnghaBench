#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t size; char const** values; int /*<<< orphan*/ * keywords; } ;
typedef  size_t Index ;

/* Variables and functions */
 TYPE_1__ ConnParams ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

const char *
GetConnParam(const char *keyword)
{
	Index i = 0;

	for (i = 0; i < ConnParams.size; i++)
	{
		if (strcmp(keyword, ConnParams.keywords[i]) == 0)
		{
			return ConnParams.values[i];
		}
	}

	return NULL;
}