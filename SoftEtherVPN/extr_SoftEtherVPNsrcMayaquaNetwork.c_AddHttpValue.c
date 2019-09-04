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
struct TYPE_3__ {int /*<<< orphan*/  ValueList; } ;
typedef  int /*<<< orphan*/  HTTP_VALUE ;
typedef  TYPE_1__ HTTP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  FreeHttpValue (int /*<<< orphan*/ *) ; 
 scalar_t__ HTTP_HEADER_MAX_LINES ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

void AddHttpValue(HTTP_HEADER *header, HTTP_VALUE *value)
{
	// Validate arguments
	if (header == NULL || value == NULL)
	{
		return;
	}

	if (LIST_NUM(header->ValueList) < HTTP_HEADER_MAX_LINES)
	{
		Insert(header->ValueList, value);
	}
	else
	{
		FreeHttpValue(value);
	}
}