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
struct TYPE_3__ {int documentEntity; scalar_t__ inEntityValue; scalar_t__ includeLevel; int /*<<< orphan*/  handler; } ;
typedef  TYPE_1__ PROLOG_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  prolog0 ; 

void
XmlPrologStateInit(PROLOG_STATE *state)
{
  state->handler = prolog0;
#ifdef XML_DTD
  state->documentEntity = 1;
  state->includeLevel = 0;
  state->inEntityValue = 0;
#endif /* XML_DTD */
}