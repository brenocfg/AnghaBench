#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct radeon_mode_info {TYPE_2__* atom_context; } ;
struct radeon_device {struct radeon_mode_info mode_info; } ;
struct radeon_atom_ss {int /*<<< orphan*/  refdiv; int /*<<< orphan*/  range; int /*<<< orphan*/  delay; int /*<<< orphan*/  step; int /*<<< orphan*/  type; int /*<<< orphan*/  percentage; } ;
struct _ATOM_SPREAD_SPECTRUM_INFO {TYPE_1__* asSS_Info; } ;
struct TYPE_4__ {int bios; } ;
struct TYPE_3__ {int ucSS_Id; int /*<<< orphan*/  ucRecommendedRef_Div; int /*<<< orphan*/  ucSS_Range; int /*<<< orphan*/  ucSS_Delay; int /*<<< orphan*/  ucSS_Step; int /*<<< orphan*/  ucSpreadSpectrumType; int /*<<< orphan*/  usSpreadSpectrumPercentage; } ;
typedef  int /*<<< orphan*/  ATOM_SPREAD_SPECTRUM_ASSIGNMENT ;
typedef  int /*<<< orphan*/  ATOM_COMMON_TABLE_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPLL_SS_Info ; 
 scalar_t__ atom_parse_data_header (TYPE_2__*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct radeon_atom_ss*,int /*<<< orphan*/ ,int) ; 

bool radeon_atombios_get_ppll_ss_info(struct radeon_device *rdev,
				      struct radeon_atom_ss *ss,
				      int id)
{
	struct radeon_mode_info *mode_info = &rdev->mode_info;
	int index = GetIndexIntoMasterTable(DATA, PPLL_SS_Info);
	uint16_t data_offset, size;
	struct _ATOM_SPREAD_SPECTRUM_INFO *ss_info;
	uint8_t frev, crev;
	int i, num_indices;

	memset(ss, 0, sizeof(struct radeon_atom_ss));
	if (atom_parse_data_header(mode_info->atom_context, index, &size,
				   &frev, &crev, &data_offset)) {
		ss_info =
			(struct _ATOM_SPREAD_SPECTRUM_INFO *)(mode_info->atom_context->bios + data_offset);

		num_indices = (size - sizeof(ATOM_COMMON_TABLE_HEADER)) /
			sizeof(ATOM_SPREAD_SPECTRUM_ASSIGNMENT);

		for (i = 0; i < num_indices; i++) {
			if (ss_info->asSS_Info[i].ucSS_Id == id) {
				ss->percentage =
					le16_to_cpu(ss_info->asSS_Info[i].usSpreadSpectrumPercentage);
				ss->type = ss_info->asSS_Info[i].ucSpreadSpectrumType;
				ss->step = ss_info->asSS_Info[i].ucSS_Step;
				ss->delay = ss_info->asSS_Info[i].ucSS_Delay;
				ss->range = ss_info->asSS_Info[i].ucSS_Range;
				ss->refdiv = ss_info->asSS_Info[i].ucRecommendedRef_Div;
				return true;
			}
		}
	}
	return false;
}