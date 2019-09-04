#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int last_byte; unsigned char Id; int Class_Id; int CSn_Id; int Msg_offset; int Msg_length; int Layer_nb; } ;
typedef  TYPE_1__ opj_jpt_msg_header_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 unsigned char cio_read (int /*<<< orphan*/ *,int) ; 
 void* jpt_read_VBAS_info (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jpt_reinit_msg_header (TYPE_1__*) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void jpt_read_msg_header(opj_common_ptr cinfo, opj_cio_t *cio, opj_jpt_msg_header_t *header) {
	unsigned char elmt, Class = 0, CSn = 0;
	jpt_reinit_msg_header(header);

	/* ------------- */
	/* VBAS : Bin-ID */
	/* ------------- */
	elmt = cio_read(cio, 1);

	/* See for Class and CSn */
	switch ((elmt >> 5) & 0x03) {
		case 0:
			opj_event_msg(cinfo, EVT_ERROR, "Forbidden value encounter in message header !!\n");
			break;
		case 1:
			Class = 0;
			CSn = 0;
			break;
		case 2:
			Class = 1;
			CSn = 0;
			break;
		case 3:
			Class = 1;
			CSn = 1;
			break;
		default:
			break;
	}

	/* see information on bits 'c' [p 10 : A.2.1 general, ISO/IEC FCD 15444-9] */
	if (((elmt >> 4) & 0x01) == 1)
		header->last_byte = 1;

	/* In-class identifier */
	header->Id |= (elmt & 0x0f);
	if ((elmt >> 7) == 1)
		header->Id = jpt_read_VBAS_info(cio, header->Id);

	/* ------------ */
	/* VBAS : Class */
	/* ------------ */
	if (Class == 1) {
		header->Class_Id = 0;
		header->Class_Id = jpt_read_VBAS_info(cio, header->Class_Id);
	}

	/* ---------- */
	/* VBAS : CSn */
	/* ---------- */
	if (CSn == 1) {
		header->CSn_Id = 0;
		header->CSn_Id = jpt_read_VBAS_info(cio, header->CSn_Id);
	}

	/* ----------------- */
	/* VBAS : Msg_offset */
	/* ----------------- */
	header->Msg_offset = jpt_read_VBAS_info(cio, header->Msg_offset);

	/* ----------------- */
	/* VBAS : Msg_length */
	/* ----------------- */
	header->Msg_length = jpt_read_VBAS_info(cio, header->Msg_length);

	/* ---------- */
	/* VBAS : Aux */
	/* ---------- */
	if ((header->Class_Id & 0x01) == 1) {
		header->Layer_nb = 0;
		header->Layer_nb = jpt_read_VBAS_info(cio, header->Layer_nb);
	}
}