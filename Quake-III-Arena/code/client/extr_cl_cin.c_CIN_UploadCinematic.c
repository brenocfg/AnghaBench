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
struct TYPE_6__ {int playonwalls; scalar_t__ dirty; int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {scalar_t__ integer; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* UploadCinematic ) (int,int,int,int,int /*<<< orphan*/ ,int,scalar_t__) ;} ;

/* Variables and functions */
 int MAX_VIDEO_HANDLES ; 
 TYPE_3__* cinTable ; 
 TYPE_2__* cl_inGameVideo ; 
 scalar_t__ qfalse ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (int,int,int,int,int /*<<< orphan*/ ,int,scalar_t__) ; 

void CIN_UploadCinematic(int handle) {
	if (handle >= 0 && handle < MAX_VIDEO_HANDLES) {
		if (!cinTable[handle].buf) {
			return;
		}
		if (cinTable[handle].playonwalls <= 0 && cinTable[handle].dirty) {
			if (cinTable[handle].playonwalls == 0) {
				cinTable[handle].playonwalls = -1;
			} else {
				if (cinTable[handle].playonwalls == -1) {
					cinTable[handle].playonwalls = -2;
				} else {
					cinTable[handle].dirty = qfalse;
				}
			}
		}
		re.UploadCinematic( 256, 256, 256, 256, cinTable[handle].buf, handle, cinTable[handle].dirty);
		if (cl_inGameVideo->integer == 0 && cinTable[handle].playonwalls == 1) {
			cinTable[handle].playonwalls--;
		}
	}
}