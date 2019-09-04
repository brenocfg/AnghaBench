#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* Rows; void* Columns; } ;
typedef  TYPE_1__ CT ;

/* Variables and functions */
 void* NewList (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

CT *CtNew()
{
	CT *ct;

	ct = ZeroMalloc(sizeof(CT));
	ct->Columns = NewList(NULL);
	ct->Rows = NewList(NULL);

	return ct;
}