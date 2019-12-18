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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int Size; void* UniStr; } ;
typedef  TYPE_1__ VALUE ;

/* Variables and functions */
 void* Malloc (int) ; 
 int /*<<< orphan*/  UniStrCpy (void*,int,int /*<<< orphan*/ *) ; 
 int UniStrSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniTrim (void*) ; 

VALUE *NewUniStrValue(wchar_t *str)
{
	VALUE *v;
	// Validate arguments
	if (str == NULL)
	{
		return NULL;
	}

	// Memory allocation
	v = Malloc(sizeof(VALUE));

	// String copy
	v->Size = UniStrSize(str);
	v->UniStr = Malloc(v->Size);
	UniStrCpy(v->UniStr, v->Size, str);

	UniTrim(v->UniStr);

	return v;
}