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
struct TYPE_2__ {int size; int maxSize; int /*<<< orphan*/ ** values; void** keywords; } ;

/* Variables and functions */
 TYPE_1__ ConnParams ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 void* strdup (char const*) ; 

void
AddConnParam(const char *keyword, const char *value)
{
	if (ConnParams.size + 1 >= ConnParams.maxSize)
	{
		/* hopefully this error is only seen by developers */
		ereport(ERROR, (errcode(ERRCODE_INSUFFICIENT_RESOURCES),
						errmsg("ConnParams arrays bound check failed")));
	}

	ConnParams.keywords[ConnParams.size] = strdup(keyword);
	ConnParams.values[ConnParams.size] = strdup(value);
	ConnParams.size++;

	ConnParams.keywords[ConnParams.size] = ConnParams.values[ConnParams.size] = NULL;
}