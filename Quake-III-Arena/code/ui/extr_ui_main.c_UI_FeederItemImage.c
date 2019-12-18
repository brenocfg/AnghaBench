#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int qhandle_t ;
struct TYPE_6__ {int characterCount; int q3HeadCount; int* q3HeadIcons; int mapCount; TYPE_2__* mapList; TYPE_1__* characterList; } ;
struct TYPE_5__ {int levelShot; int /*<<< orphan*/  imageName; } ;
struct TYPE_4__ {int headImage; int /*<<< orphan*/  imageName; } ;

/* Variables and functions */
 float FEEDER_ALLMAPS ; 
 float FEEDER_HEADS ; 
 float FEEDER_MAPS ; 
 float FEEDER_Q3HEADS ; 
 int /*<<< orphan*/  UI_SelectedHead (int,int*) ; 
 int /*<<< orphan*/  UI_SelectedMap (int,int*) ; 
 void* trap_R_RegisterShaderNoMip (int /*<<< orphan*/ ) ; 
 TYPE_3__ uiInfo ; 

__attribute__((used)) static qhandle_t UI_FeederItemImage(float feederID, int index) {
  if (feederID == FEEDER_HEADS) {
	int actual;
	UI_SelectedHead(index, &actual);
	index = actual;
	if (index >= 0 && index < uiInfo.characterCount) {
		if (uiInfo.characterList[index].headImage == -1) {
			uiInfo.characterList[index].headImage = trap_R_RegisterShaderNoMip(uiInfo.characterList[index].imageName);
		}
		return uiInfo.characterList[index].headImage;
	}
  } else if (feederID == FEEDER_Q3HEADS) {
    if (index >= 0 && index < uiInfo.q3HeadCount) {
      return uiInfo.q3HeadIcons[index];
    }
	} else if (feederID == FEEDER_ALLMAPS || feederID == FEEDER_MAPS) {
		int actual;
		UI_SelectedMap(index, &actual);
		index = actual;
		if (index >= 0 && index < uiInfo.mapCount) {
			if (uiInfo.mapList[index].levelShot == -1) {
				uiInfo.mapList[index].levelShot = trap_R_RegisterShaderNoMip(uiInfo.mapList[index].imageName);
			}
			return uiInfo.mapList[index].levelShot;
		}
	}
  return 0;
}