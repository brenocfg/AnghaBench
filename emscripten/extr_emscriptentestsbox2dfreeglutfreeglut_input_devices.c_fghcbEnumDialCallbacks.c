#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  SFG_Window ;
typedef  TYPE_1__ SFG_Enumerator ;

/* Variables and functions */
 int /*<<< orphan*/  Dials ; 
 int /*<<< orphan*/  INVOKE_WCB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fgEnumSubWindows (int /*<<< orphan*/ *,void (*) (int /*<<< orphan*/ *,TYPE_1__*),TYPE_1__*) ; 

__attribute__((used)) static void fghcbEnumDialCallbacks ( SFG_Window *window, SFG_Enumerator *enumerator )
{
    /* Built-in to INVOKE_WCB():  if window->Callbacks[CB_Dials] */
    INVOKE_WCB ( *window,Dials, ( ((int*)enumerator->data)[0], ((int*)enumerator->data)[1]) );
    fgEnumSubWindows ( window, fghcbEnumDialCallbacks, enumerator );
}