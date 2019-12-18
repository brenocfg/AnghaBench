#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int lead_in; int num_tracks; TYPE_2__* tracks; } ;
struct TYPE_6__ {int number; int offset; unsigned int num_indices; TYPE_1__* indices; } ;
struct TYPE_5__ {int number; int offset; } ;
typedef  int FLAC__bool ;
typedef  TYPE_3__ FLAC__StreamMetadata_CueSheet ;

/* Variables and functions */

FLAC__bool FLAC__format_cuesheet_is_legal(const FLAC__StreamMetadata_CueSheet *cue_sheet, FLAC__bool check_cd_da_subset, const char **violation)
{
	unsigned i, j;

	if(check_cd_da_subset) {
		if(cue_sheet->lead_in < 2 * 44100) {
			if(violation) *violation = "CD-DA cue sheet must have a lead-in length of at least 2 seconds";
			return false;
		}
		if(cue_sheet->lead_in % 588 != 0) {
			if(violation) *violation = "CD-DA cue sheet lead-in length must be evenly divisible by 588 samples";
			return false;
		}
	}

	if(cue_sheet->num_tracks == 0) {
		if(violation) *violation = "cue sheet must have at least one track (the lead-out)";
		return false;
	}

	if(check_cd_da_subset && cue_sheet->tracks[cue_sheet->num_tracks-1].number != 170) {
		if(violation) *violation = "CD-DA cue sheet must have a lead-out track number 170 (0xAA)";
		return false;
	}

	for(i = 0; i < cue_sheet->num_tracks; i++) {
		if(cue_sheet->tracks[i].number == 0) {
			if(violation) *violation = "cue sheet may not have a track number 0";
			return false;
		}

		if(check_cd_da_subset) {
			if(!((cue_sheet->tracks[i].number >= 1 && cue_sheet->tracks[i].number <= 99) || cue_sheet->tracks[i].number == 170)) {
				if(violation) *violation = "CD-DA cue sheet track number must be 1-99 or 170";
				return false;
			}
		}

		if(check_cd_da_subset && cue_sheet->tracks[i].offset % 588 != 0) {
			if(violation) {
				if(i == cue_sheet->num_tracks-1) /* the lead-out track... */
					*violation = "CD-DA cue sheet lead-out offset must be evenly divisible by 588 samples";
				else
					*violation = "CD-DA cue sheet track offset must be evenly divisible by 588 samples";
			}
			return false;
		}

		if(i < cue_sheet->num_tracks - 1) {
			if(cue_sheet->tracks[i].num_indices == 0) {
				if(violation) *violation = "cue sheet track must have at least one index point";
				return false;
			}

			if(cue_sheet->tracks[i].indices[0].number > 1) {
				if(violation) *violation = "cue sheet track's first index number must be 0 or 1";
				return false;
			}
		}

		for(j = 0; j < cue_sheet->tracks[i].num_indices; j++) {
			if(check_cd_da_subset && cue_sheet->tracks[i].indices[j].offset % 588 != 0) {
				if(violation) *violation = "CD-DA cue sheet track index offset must be evenly divisible by 588 samples";
				return false;
			}

			if(j > 0) {
				if(cue_sheet->tracks[i].indices[j].number != cue_sheet->tracks[i].indices[j-1].number + 1) {
					if(violation) *violation = "cue sheet track index numbers must increase by 1";
					return false;
				}
			}
		}
	}

	return true;
}