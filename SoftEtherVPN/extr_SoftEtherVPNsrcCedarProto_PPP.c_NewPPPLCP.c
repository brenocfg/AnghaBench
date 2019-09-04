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
typedef  void* UCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  OptionList; void* Id; void* Code; } ;
typedef  TYPE_1__ PPP_LCP ;

/* Variables and functions */
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

PPP_LCP *NewPPPLCP(UCHAR code, UCHAR id)
{
	PPP_LCP *c = ZeroMalloc(sizeof(PPP_LCP));

	c->Code = code;
	c->Id = id;
	c->OptionList = NewListFast(NULL);

	return c;
}