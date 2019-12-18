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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ version; } ;
typedef  int /*<<< orphan*/  Result ;
typedef  TYPE_1__ AM_TitleEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AM_GetTitleCount (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  AM_GetTitleInfo (int /*<<< orphan*/ ,int,scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  AM_GetTitleList (int*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  MEDIATYPE_SD ; 
 scalar_t__ R_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (int) ; 

__attribute__((used)) static int isCiaInstalled(u64 titleId, u16 version){
	u32 titlesToRetrieve;
	u32 titlesRetrieved;
	u64* titleIds;
	bool titleExists = false;
	AM_TitleEntry titleInfo;
	Result failed;

	failed = AM_GetTitleCount(MEDIATYPE_SD, &titlesToRetrieve);
	if(R_FAILED(failed))
		return -1;

	titleIds = malloc(titlesToRetrieve * sizeof(uint64_t));
	if(titleIds == NULL)
		return -1;

	failed = AM_GetTitleList(&titlesRetrieved, MEDIATYPE_SD, titlesToRetrieve, titleIds);
	if(R_FAILED(failed))
		return -1;

	for(u32 titlesToCheck = 0; titlesToCheck < titlesRetrieved; titlesToCheck++){
		if(titleIds[titlesToCheck] == titleId){
			titleExists = true;
			break;
		}
	}

	free(titleIds);

	if(titleExists){
		failed = AM_GetTitleInfo(MEDIATYPE_SD, 1 /*titleCount*/, &titleId, &titleInfo);
		if(R_FAILED(failed))
			return -1;

		if(titleInfo.version == version)
			return 1;
	}

	return 0;
}