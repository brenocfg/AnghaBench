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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Data; } ;
typedef  TYPE_1__ HTTP_VALUE ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;

/* Variables and functions */
 TYPE_1__* GetHttpValue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ToInt (int /*<<< orphan*/ ) ; 

UINT GetContentLength(HTTP_HEADER *header)
{
	UINT ret;
	HTTP_VALUE *v;
	// Validate arguments
	if (header == NULL)
	{
		return 0;
	}

	v = GetHttpValue(header, "Content-Length");
	if (v == NULL)
	{
		return 0;
	}

	ret = ToInt(v->Data);

	return ret;
}