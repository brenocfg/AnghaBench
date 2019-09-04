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
typedef  int /*<<< orphan*/  VALUE ;
typedef  size_t UINT ;
struct TYPE_3__ {size_t type; size_t num_value; int /*<<< orphan*/ ** values; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ELEMENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  WriteBufInt (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  WriteBufStr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

void WriteElement(BUF *b, ELEMENT *e)
{
	UINT i;
	// Validate arguments
	if (b == NULL || e == NULL)
	{
		return;
	}

	// Name
	WriteBufStr(b, e->name);
	// Type of item
	WriteBufInt(b, e->type);
	// Number of items
	WriteBufInt(b, e->num_value);
	// VALUE
	for (i = 0;i < e->num_value;i++)
	{
		VALUE *v = e->values[i];
		WriteValue(b, v, e->type);
	}
}