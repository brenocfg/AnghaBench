#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  multiDef_t ;
typedef  int /*<<< orphan*/  modelDef_t ;
typedef  int /*<<< orphan*/  listBoxDef_t ;
struct TYPE_4__ {scalar_t__ type; void* typeData; } ;
typedef  TYPE_1__ itemDef_t ;
struct TYPE_5__ {scalar_t__ maxPaintChars; } ;
typedef  TYPE_2__ editFieldDef_t ;

/* Variables and functions */
 scalar_t__ ITEM_TYPE_BIND ; 
 scalar_t__ ITEM_TYPE_EDITFIELD ; 
 scalar_t__ ITEM_TYPE_LISTBOX ; 
 scalar_t__ ITEM_TYPE_MODEL ; 
 scalar_t__ ITEM_TYPE_MULTI ; 
 scalar_t__ ITEM_TYPE_NUMERICFIELD ; 
 scalar_t__ ITEM_TYPE_SLIDER ; 
 scalar_t__ ITEM_TYPE_TEXT ; 
 scalar_t__ ITEM_TYPE_YESNO ; 
 scalar_t__ MAX_EDITFIELD ; 
 void* UI_Alloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void Item_ValidateTypeData(itemDef_t *item) {
	if (item->typeData) {
		return;
	}

	if (item->type == ITEM_TYPE_LISTBOX) {
		item->typeData = UI_Alloc(sizeof(listBoxDef_t));
		memset(item->typeData, 0, sizeof(listBoxDef_t));
	} else if (item->type == ITEM_TYPE_EDITFIELD || item->type == ITEM_TYPE_NUMERICFIELD || item->type == ITEM_TYPE_YESNO || item->type == ITEM_TYPE_BIND || item->type == ITEM_TYPE_SLIDER || item->type == ITEM_TYPE_TEXT) {
		item->typeData = UI_Alloc(sizeof(editFieldDef_t));
		memset(item->typeData, 0, sizeof(editFieldDef_t));
		if (item->type == ITEM_TYPE_EDITFIELD) {
			if (!((editFieldDef_t *) item->typeData)->maxPaintChars) {
				((editFieldDef_t *) item->typeData)->maxPaintChars = MAX_EDITFIELD;
			}
		}
	} else if (item->type == ITEM_TYPE_MULTI) {
		item->typeData = UI_Alloc(sizeof(multiDef_t));
	} else if (item->type == ITEM_TYPE_MODEL) {
		item->typeData = UI_Alloc(sizeof(modelDef_t));
	}
}