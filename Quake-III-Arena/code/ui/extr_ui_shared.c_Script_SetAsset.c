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
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ itemDef_t ;

/* Variables and functions */
 scalar_t__ ITEM_TYPE_MODEL ; 
 scalar_t__ String_Parse (char**,char const**) ; 

void Script_SetAsset(itemDef_t *item, char **args) {
  const char *name;
  // expecting name to set asset to
  if (String_Parse(args, &name)) {
    // check for a model 
    if (item->type == ITEM_TYPE_MODEL) {
    }
  }
}