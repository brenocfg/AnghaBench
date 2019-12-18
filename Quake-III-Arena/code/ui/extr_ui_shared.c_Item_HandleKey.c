#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
struct TYPE_10__ {int type; } ;
typedef  TYPE_1__ itemDef_t ;

/* Variables and functions */
#define  ITEM_TYPE_BIND 139 
#define  ITEM_TYPE_BUTTON 138 
#define  ITEM_TYPE_CHECKBOX 137 
#define  ITEM_TYPE_COMBO 136 
#define  ITEM_TYPE_EDITFIELD 135 
#define  ITEM_TYPE_LISTBOX 134 
#define  ITEM_TYPE_MULTI 133 
#define  ITEM_TYPE_NUMERICFIELD 132 
#define  ITEM_TYPE_OWNERDRAW 131 
#define  ITEM_TYPE_RADIOBUTTON 130 
#define  ITEM_TYPE_SLIDER 129 
#define  ITEM_TYPE_YESNO 128 
 scalar_t__ Item_Bind_HandleKey (TYPE_1__*,int,scalar_t__) ; 
 scalar_t__ Item_ListBox_HandleKey (TYPE_1__*,int,scalar_t__,scalar_t__) ; 
 scalar_t__ Item_Multi_HandleKey (TYPE_1__*,int) ; 
 scalar_t__ Item_OwnerDraw_HandleKey (TYPE_1__*,int) ; 
 scalar_t__ Item_Slider_HandleKey (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  Item_StartCapture (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Item_StopCapture (int /*<<< orphan*/ *) ; 
 scalar_t__ Item_YesNo_HandleKey (TYPE_1__*,int) ; 
 int K_MOUSE1 ; 
 int K_MOUSE2 ; 
 int K_MOUSE3 ; 
 int /*<<< orphan*/ * captureData ; 
 int /*<<< orphan*/ * captureFunc ; 
 int /*<<< orphan*/ * itemCapture ; 
 scalar_t__ qfalse ; 

qboolean Item_HandleKey(itemDef_t *item, int key, qboolean down) {

	if (itemCapture) {
		Item_StopCapture(itemCapture);
		itemCapture = NULL;
		captureFunc = NULL;
		captureData = NULL;
	} else {
	  // bk001206 - parentheses
		if ( down && ( key == K_MOUSE1 || key == K_MOUSE2 || key == K_MOUSE3 ) ) {
			Item_StartCapture(item, key);
		}
	}

	if (!down) {
		return qfalse;
	}

  switch (item->type) {
    case ITEM_TYPE_BUTTON:
      return qfalse;
      break;
    case ITEM_TYPE_RADIOBUTTON:
      return qfalse;
      break;
    case ITEM_TYPE_CHECKBOX:
      return qfalse;
      break;
    case ITEM_TYPE_EDITFIELD:
    case ITEM_TYPE_NUMERICFIELD:
      //return Item_TextField_HandleKey(item, key);
      return qfalse;
      break;
    case ITEM_TYPE_COMBO:
      return qfalse;
      break;
    case ITEM_TYPE_LISTBOX:
      return Item_ListBox_HandleKey(item, key, down, qfalse);
      break;
    case ITEM_TYPE_YESNO:
      return Item_YesNo_HandleKey(item, key);
      break;
    case ITEM_TYPE_MULTI:
      return Item_Multi_HandleKey(item, key);
      break;
    case ITEM_TYPE_OWNERDRAW:
      return Item_OwnerDraw_HandleKey(item, key);
      break;
    case ITEM_TYPE_BIND:
			return Item_Bind_HandleKey(item, key, down);
      break;
    case ITEM_TYPE_SLIDER:
      return Item_Slider_HandleKey(item, key, down);
      break;
    //case ITEM_TYPE_IMAGE:
    //  Item_Image_Paint(item);
    //  break;
    default:
      return qfalse;
      break;
  }

  //return qfalse;
}