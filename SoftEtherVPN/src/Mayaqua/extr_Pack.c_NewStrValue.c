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
struct TYPE_3__ {int Size; void* Str; } ;
typedef  TYPE_1__ VALUE ;

/* Variables and functions */
 void* Malloc (int) ; 
 int /*<<< orphan*/  StrCpy (void*,int,char*) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  Trim (void*) ; 

VALUE *NewStrValue(char *str)
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
	v->Size = StrLen(str) + 1;
	v->Str = Malloc(v->Size);
	StrCpy(v->Str, v->Size, str);

	Trim(v->Str);

	return v;
}