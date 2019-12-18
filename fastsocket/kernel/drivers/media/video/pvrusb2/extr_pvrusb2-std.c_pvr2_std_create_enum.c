#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int v4l2_std_id ;
struct v4l2_standard {unsigned int index; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int CSTD_ATSC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int PVR2_TRACE_STD ; 
 struct v4l2_standard* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ match_std (int) ; 
 scalar_t__ pvr2_std_fill (struct v4l2_standard*,int) ; 
 unsigned int pvr2_std_id_to_str (char*,int,int) ; 
 int /*<<< orphan*/  pvr2_trace (int,char*,unsigned int,...) ; 
 int pvrusb2_debug ; 
 int* std_mixes ; 

struct v4l2_standard *pvr2_std_create_enum(unsigned int *countptr,
					   v4l2_std_id id)
{
	unsigned int std_cnt = 0;
	unsigned int idx,bcnt,idx2;
	v4l2_std_id idmsk,cmsk,fmsk;
	struct v4l2_standard *stddefs;

	if (pvrusb2_debug & PVR2_TRACE_STD) {
		char buf[100];
		bcnt = pvr2_std_id_to_str(buf,sizeof(buf),id);
		pvr2_trace(
			PVR2_TRACE_STD,"Mapping standards mask=0x%x (%.*s)",
			(int)id,bcnt,buf);
	}

	*countptr = 0;
	std_cnt = 0;
	fmsk = 0;
	for (idmsk = 1, cmsk = id; cmsk; idmsk <<= 1) {
		if (!(idmsk & cmsk)) continue;
		cmsk &= ~idmsk;
		if (match_std(idmsk)) {
			std_cnt++;
			continue;
		}
		fmsk |= idmsk;
	}

	for (idx2 = 0; idx2 < ARRAY_SIZE(std_mixes); idx2++) {
		if ((id & std_mixes[idx2]) == std_mixes[idx2]) std_cnt++;
	}

	/* Don't complain about ATSC standard values */
	fmsk &= ~CSTD_ATSC;

	if (fmsk) {
		char buf[100];
		bcnt = pvr2_std_id_to_str(buf,sizeof(buf),fmsk);
		pvr2_trace(
			PVR2_TRACE_ERROR_LEGS,
			"WARNING:"
			" Failed to classify the following standard(s): %.*s",
			bcnt,buf);
	}

	pvr2_trace(PVR2_TRACE_STD,"Setting up %u unique standard(s)",
		   std_cnt);
	if (!std_cnt) return NULL; // paranoia

	stddefs = kzalloc(sizeof(struct v4l2_standard) * std_cnt,
			  GFP_KERNEL);
	for (idx = 0; idx < std_cnt; idx++) stddefs[idx].index = idx;

	idx = 0;

	/* Enumerate potential special cases */
	for (idx2 = 0; (idx2 < ARRAY_SIZE(std_mixes)) && (idx < std_cnt);
	     idx2++) {
		if (!(id & std_mixes[idx2])) continue;
		if (pvr2_std_fill(stddefs+idx,std_mixes[idx2])) idx++;
	}
	/* Now enumerate individual pieces */
	for (idmsk = 1, cmsk = id; cmsk && (idx < std_cnt); idmsk <<= 1) {
		if (!(idmsk & cmsk)) continue;
		cmsk &= ~idmsk;
		if (!pvr2_std_fill(stddefs+idx,idmsk)) continue;
		idx++;
	}

	*countptr = std_cnt;
	return stddefs;
}