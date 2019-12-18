#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
struct TYPE_6__ {int Length; int MaximumLength; void* Buffer; } ;
struct TYPE_8__ {TYPE_1__ String; } ;
typedef  TYPE_3__ SL_UNICODE ;

/* Variables and functions */
 int /*<<< orphan*/  SlCopy (void*,int /*<<< orphan*/ ,int) ; 
 void* SlZeroMalloc (int) ; 

SL_UNICODE *SlNewUnicodeFromUnicodeString(UNICODE_STRING *src)
{
	SL_UNICODE *u;
	// Validate arguments
	if (src == NULL)
	{
		return NULL;
	}

	// Memory allocation
	u = SlZeroMalloc(sizeof(SL_UNICODE));
	if (u == NULL)
	{
		return NULL;
	}

	u->String.Length = u->String.MaximumLength = src->Length;
	
	u->String.Buffer = SlZeroMalloc(src->Length);
	SlCopy(u->String.Buffer, src->Buffer, src->Length);

	return u;
}