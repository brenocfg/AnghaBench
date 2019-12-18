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
typedef  int /*<<< orphan*/  rectDef_t ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ itemDef_t ;

/* Variables and functions */
 scalar_t__ Float_Parse (char**,float*) ; 
 scalar_t__ Int_Parse (char**,int*) ; 
 int /*<<< orphan*/  Menu_TransitionItemByName (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,float) ; 
 scalar_t__ Rect_Parse (char**,int /*<<< orphan*/ *) ; 
 scalar_t__ String_Parse (char**,char const**) ; 

void Script_Transition(itemDef_t *item, char **args) {
  const char *name;
	rectDef_t rectFrom, rectTo;
  int time;
	float amt;

  if (String_Parse(args, &name)) {
    if ( Rect_Parse(args, &rectFrom) && Rect_Parse(args, &rectTo) && Int_Parse(args, &time) && Float_Parse(args, &amt)) {
      Menu_TransitionItemByName(item->parent, name, rectFrom, rectTo, time, amt);
    }
  }
}