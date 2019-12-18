#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int s32 ;
struct TYPE_9__ {TYPE_1__* palhead; TYPE_2__* imghead; } ;
struct TYPE_8__ {size_t ntextures; TYPE_4__* texdesc; scalar_t__ tpl_file; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {char* data; } ;
struct TYPE_6__ {char* data; } ;
typedef  TYPE_1__ TPLPalHeader ;
typedef  TYPE_2__ TPLImgHeader ;
typedef  TYPE_3__ TPLFile ;
typedef  TYPE_4__ TPLDescHeader ;
typedef  scalar_t__ FHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  TPL_FILE_TYPE_MEM ; 
 int TPL_HDR_DESCR_FIELD ; 
 int TPL_HDR_NTEXTURE_FIELD ; 

s32 TPL_OpenTPLFromMemory(TPLFile* tdf, void *memory,u32 len)
{
	u32 c,pos;
	const char *p = memory;
	TPLDescHeader *deschead = NULL;
	TPLImgHeader *imghead = NULL;
	TPLPalHeader *palhead = NULL;

	if(!memory || !len) return -1;		//TPL_ERR_INVALID

	tdf->type = TPL_FILE_TYPE_MEM;
	tdf->tpl_file = (FHANDLE)NULL;

	//version = *(u32*)(p + TPL_HDR_VERSION_FIELD);
	tdf->ntextures = *(u32*)(p + TPL_HDR_NTEXTURE_FIELD);

	deschead = (TPLDescHeader*)(p + TPL_HDR_DESCR_FIELD);
	for(c=0;c<tdf->ntextures;c++) {
		imghead = NULL;
		palhead = NULL;

		pos = (u32)deschead[c].imghead;
		imghead = (TPLImgHeader*)(p + pos);

		pos = (u32)imghead->data;
		imghead->data = (char*)(p + pos);

		pos = (u32)deschead[c].palhead;
		if(pos) {
			palhead = (TPLPalHeader*)(p + pos);

			pos = (u32)palhead->data;
			palhead->data = (char*)(p + pos);
		}
		deschead[c].imghead = imghead;
		deschead[c].palhead = palhead;
	}
	tdf->texdesc = deschead;

	return 1;
}