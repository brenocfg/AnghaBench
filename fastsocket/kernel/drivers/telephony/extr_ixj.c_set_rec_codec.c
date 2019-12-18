#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  low; } ;
struct TYPE_9__ {int /*<<< orphan*/  g729_loaded; int /*<<< orphan*/  ts85_loaded; } ;
struct TYPE_8__ {int low; } ;
struct TYPE_7__ {int low; } ;
struct TYPE_11__ {int rec_codec; int rec_frame_size; int rec_mode; int /*<<< orphan*/  read_buffer_size; int /*<<< orphan*/ * read_buffer; TYPE_4__ baseframe; TYPE_3__ flags; TYPE_2__ dsp; TYPE_1__ ver; } ;
typedef  TYPE_5__ IXJ ;

/* Variables and functions */
#define  ALAW 140 
#define  G723_53 139 
#define  G723_63 138 
#define  G728 137 
#define  G729 136 
#define  G729B 135 
#define  LINEAR16 134 
#define  LINEAR8 133 
#define  TS41 132 
#define  TS48 131 
#define  TS85 130 
#define  ULAW 129 
#define  WSS 128 
 int /*<<< orphan*/  ixj_convert_loaded ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_rec_codec(IXJ *j, int rate)
{
	int retval = 0;

	j->rec_codec = rate;

	switch (rate) {
	case G723_63:
		if (j->ver.low != 0x12 || ixj_convert_loaded) {
			j->rec_frame_size = 12;
			j->rec_mode = 0;
		} else {
			retval = 1;
		}
		break;
	case G723_53:
		if (j->ver.low != 0x12 || ixj_convert_loaded) {
			j->rec_frame_size = 10;
			j->rec_mode = 0;
		} else {
			retval = 1;
		}
		break;
	case TS85:
		if (j->dsp.low == 0x20 || j->flags.ts85_loaded) {
			j->rec_frame_size = 16;
			j->rec_mode = 0;
		} else {
			retval = 1;
		}
		break;
	case TS48:
		if (j->ver.low != 0x12 || ixj_convert_loaded) {
			j->rec_frame_size = 9;
			j->rec_mode = 0;
		} else {
			retval = 1;
		}
		break;
	case TS41:
		if (j->ver.low != 0x12 || ixj_convert_loaded) {
			j->rec_frame_size = 8;
			j->rec_mode = 0;
		} else {
			retval = 1;
		}
		break;
	case G728:
		if (j->dsp.low != 0x20) {
			j->rec_frame_size = 48;
			j->rec_mode = 0;
		} else {
			retval = 1;
		}
		break;
	case G729:
		if (j->dsp.low != 0x20) {
			if (!j->flags.g729_loaded) {
				retval = 1;
				break;
			}
			switch (j->baseframe.low) {
			case 0xA0:
				j->rec_frame_size = 10;
				break;
			case 0x50:
				j->rec_frame_size = 5;
				break;
			default:
				j->rec_frame_size = 15;
				break;
			}
			j->rec_mode = 0;
		} else {
			retval = 1;
		}
		break;
	case G729B:
		if (j->dsp.low != 0x20) {
			if (!j->flags.g729_loaded) {
				retval = 1;
				break;
			}
			switch (j->baseframe.low) {
			case 0xA0:
				j->rec_frame_size = 12;
				break;
			case 0x50:
				j->rec_frame_size = 6;
				break;
			default:
				j->rec_frame_size = 18;
				break;
			}
			j->rec_mode = 0;
		} else {
			retval = 1;
		}
		break;
	case ULAW:
		switch (j->baseframe.low) {
		case 0xA0:
			j->rec_frame_size = 80;
			break;
		case 0x50:
			j->rec_frame_size = 40;
			break;
		default:
			j->rec_frame_size = 120;
			break;
		}
		j->rec_mode = 4;
		break;
	case ALAW:
		switch (j->baseframe.low) {
		case 0xA0:
			j->rec_frame_size = 80;
			break;
		case 0x50:
			j->rec_frame_size = 40;
			break;
		default:
			j->rec_frame_size = 120;
			break;
		}
		j->rec_mode = 4;
		break;
	case LINEAR16:
		switch (j->baseframe.low) {
		case 0xA0:
			j->rec_frame_size = 160;
			break;
		case 0x50:
			j->rec_frame_size = 80;
			break;
		default:
			j->rec_frame_size = 240;
			break;
		}
		j->rec_mode = 5;
		break;
	case LINEAR8:
		switch (j->baseframe.low) {
		case 0xA0:
			j->rec_frame_size = 80;
			break;
		case 0x50:
			j->rec_frame_size = 40;
			break;
		default:
			j->rec_frame_size = 120;
			break;
		}
		j->rec_mode = 6;
		break;
	case WSS:
		switch (j->baseframe.low) {
		case 0xA0:
			j->rec_frame_size = 80;
			break;
		case 0x50:
			j->rec_frame_size = 40;
			break;
		default:
			j->rec_frame_size = 120;
			break;
		}
		j->rec_mode = 7;
		break;
	default:
		kfree(j->read_buffer);
		j->rec_frame_size = 0;
		j->rec_mode = -1;
		j->read_buffer = NULL;
		j->read_buffer_size = 0;
		retval = 1;
		break;
	}
	return retval;
}