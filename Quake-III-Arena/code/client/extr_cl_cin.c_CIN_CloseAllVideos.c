#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* fileName; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIN_StopCinematic (int) ; 
 int MAX_VIDEO_HANDLES ; 
 TYPE_1__* cinTable ; 

void CIN_CloseAllVideos(void) {
	int		i;

	for ( i = 0 ; i < MAX_VIDEO_HANDLES ; i++ ) {
		if (cinTable[i].fileName[0] != 0 ) {
			CIN_StopCinematic(i);
		}
	}
}