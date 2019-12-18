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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_frame_extra {int /*<<< orphan*/  r_b_def_p_cnt; int /*<<< orphan*/  g_def_p_cnt; int /*<<< orphan*/  bl_oddcol; int /*<<< orphan*/  bl_evencol; } ;
struct vfe_endframe {int /*<<< orphan*/  redbluedefectpixelcount; int /*<<< orphan*/  greendefectpixelcount; int /*<<< orphan*/  blackleveloddcolumn; int /*<<< orphan*/  blacklevelevencolumn; int /*<<< orphan*/  cbcr_address; int /*<<< orphan*/  y_address; } ;
struct msm_vfe_phy_info {int /*<<< orphan*/  sbuf_phy; int /*<<< orphan*/  cbcr_phy; int /*<<< orphan*/  y_phy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  enum vfe_resp_msg { ____Placeholder_vfe_resp_msg } vfe_resp_msg ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  VFE_MSG_OUTPUT1 131 
#define  VFE_MSG_OUTPUT2 130 
#define  VFE_MSG_STATS_AF 129 
#define  VFE_MSG_STATS_WE 128 
 void* extdata ; 
 int /*<<< orphan*/  extlen ; 

__attribute__((used)) static void vfe_7x_convert(struct msm_vfe_phy_info *pinfo,
		enum vfe_resp_msg type,
		void *data, void **ext, int32_t *elen)
{
	switch (type) {
	case VFE_MSG_OUTPUT1:
	case VFE_MSG_OUTPUT2: {
		pinfo->y_phy = ((struct vfe_endframe *)data)->y_address;
		pinfo->cbcr_phy =
			((struct vfe_endframe *)data)->cbcr_address;

		CDBG("vfe_7x_convert, y_phy = 0x%x, cbcr_phy = 0x%x\n",
				 pinfo->y_phy, pinfo->cbcr_phy);

		((struct vfe_frame_extra *)extdata)->bl_evencol =
		((struct vfe_endframe *)data)->blacklevelevencolumn;

		((struct vfe_frame_extra *)extdata)->bl_oddcol =
		((struct vfe_endframe *)data)->blackleveloddcolumn;

		((struct vfe_frame_extra *)extdata)->g_def_p_cnt =
		((struct vfe_endframe *)data)->greendefectpixelcount;

		((struct vfe_frame_extra *)extdata)->r_b_def_p_cnt =
		((struct vfe_endframe *)data)->redbluedefectpixelcount;

		*ext  = extdata;
		*elen = extlen;
	}
		break;

	case VFE_MSG_STATS_AF:
	case VFE_MSG_STATS_WE:
		pinfo->sbuf_phy = *(uint32_t *)data;
		break;

	default:
		break;
	} /* switch */
}