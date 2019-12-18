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
struct TYPE_3__ {char* value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ KeyValuePair ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

char *fdfs_http_get_parameter(const char *param_name, KeyValuePair *params, \
		const int param_count)
{
	KeyValuePair *pCurrent;
	KeyValuePair *pEnd;

	pEnd = params + param_count;
	for (pCurrent=params; pCurrent<pEnd; pCurrent++)
	{
		if (strcmp(pCurrent->key, param_name) == 0)
		{
			return pCurrent->value;
		}
	}

	return NULL;
}