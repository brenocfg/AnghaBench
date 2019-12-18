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
typedef  int u8 ;
struct st_request {int* sense; } ;
struct st_cmdstatus {int flags; int deferred; int fixed_format; int /*<<< orphan*/  uremainder64; int /*<<< orphan*/  remainder_valid; scalar_t__ have_sense; int /*<<< orphan*/  sense_hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  scsi_get_sense_info_fld (int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_normalize_sense (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* scsi_sense_desc_find (int const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void st_analyze_sense(struct st_request *SRpnt, struct st_cmdstatus *s)
{
	const u8 *ucp;
	const u8 *sense = SRpnt->sense;

	s->have_sense = scsi_normalize_sense(SRpnt->sense,
				SCSI_SENSE_BUFFERSIZE, &s->sense_hdr);
	s->flags = 0;

	if (s->have_sense) {
		s->deferred = 0;
		s->remainder_valid =
			scsi_get_sense_info_fld(sense, SCSI_SENSE_BUFFERSIZE, &s->uremainder64);
		switch (sense[0] & 0x7f) {
		case 0x71:
			s->deferred = 1;
		case 0x70:
			s->fixed_format = 1;
			s->flags = sense[2] & 0xe0;
			break;
		case 0x73:
			s->deferred = 1;
		case 0x72:
			s->fixed_format = 0;
			ucp = scsi_sense_desc_find(sense, SCSI_SENSE_BUFFERSIZE, 4);
			s->flags = ucp ? (ucp[3] & 0xe0) : 0;
			break;
		}
	}
}