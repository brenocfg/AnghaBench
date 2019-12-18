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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ itemDef_t ;

/* Variables and functions */
 scalar_t__ Float_Parse (char**,float*) ; 
 scalar_t__ Int_Parse (char**,int*) ; 
 int /*<<< orphan*/  Menu_OrbitItemByName (int /*<<< orphan*/ ,char const*,float,float,float,float,int) ; 
 scalar_t__ String_Parse (char**,char const**) ; 

void Script_Orbit(itemDef_t *item, char **args) {
  const char *name;
  float cx, cy, x, y;
  int time;

  if (String_Parse(args, &name)) {
    if ( Float_Parse(args, &x) && Float_Parse(args, &y) && Float_Parse(args, &cx) && Float_Parse(args, &cy) && Int_Parse(args, &time) ) {
      Menu_OrbitItemByName(item->parent, name, x, y, cx, cy, time);
    }
  }
}