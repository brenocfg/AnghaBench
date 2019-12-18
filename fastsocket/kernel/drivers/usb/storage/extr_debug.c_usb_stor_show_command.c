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
struct scsi_cmnd {int cmd_len; int /*<<< orphan*/ * cmnd; } ;

/* Variables and functions */
#define  ALLOW_MEDIUM_REMOVAL 211 
#define  CHANGE_DEFINITION 210 
#define  COMPARE 209 
#define  COPY 208 
#define  COPY_VERIFY 207 
#define  ERASE 206 
#define  FORMAT_UNIT 205 
#define  GPCMD_BLANK 204 
#define  GPCMD_CLOSE_TRACK 203 
#define  GPCMD_GET_EVENT_STATUS_NOTIFICATION 202 
#define  GPCMD_MECHANISM_STATUS 201 
#define  GPCMD_PAUSE_RESUME 200 
#define  GPCMD_PLAY_AUDIO_10 199 
#define  GPCMD_PLAY_AUDIO_MSF 198 
#define  GPCMD_READ_CD 197 
#define  GPCMD_READ_CD_MSF 196 
#define  GPCMD_READ_DISC_INFO 195 
#define  GPCMD_READ_HEADER 194 
#define  GPCMD_READ_SUBCHANNEL 193 
#define  GPCMD_READ_TRACK_RZONE_INFO 192 
#define  GPCMD_REPAIR_RZONE_TRACK 191 
#define  GPCMD_RESERVE_RZONE_TRACK 190 
#define  GPCMD_SCAN 189 
#define  GPCMD_SEND_OPC 188 
#define  GPCMD_SET_SPEED 187 
#define  GPCMD_STOP_PLAY_SCAN 186 
#define  INQUIRY 185 
#define  LOCK_UNLOCK_CACHE 184 
#define  LOG_SELECT 183 
#define  LOG_SENSE 182 
#define  MEDIUM_SCAN 181 
#define  MODE_SELECT 180 
#define  MODE_SELECT_10 179 
#define  MODE_SENSE 178 
#define  MODE_SENSE_10 177 
#define  MOVE_MEDIUM 176 
#define  READ_10 175 
#define  READ_12 174 
#define  READ_6 173 
#define  READ_BLOCK_LIMITS 172 
#define  READ_BUFFER 171 
#define  READ_CAPACITY 170 
#define  READ_DEFECT_DATA 169 
#define  READ_ELEMENT_STATUS 168 
#define  READ_LONG 167 
#define  READ_POSITION 166 
#define  READ_REVERSE 165 
#define  READ_TOC 164 
#define  REASSIGN_BLOCKS 163 
#define  RECEIVE_DIAGNOSTIC 162 
#define  RECOVER_BUFFERED_DATA 161 
#define  RELEASE 160 
#define  REPORT_LUNS 159 
#define  REQUEST_SENSE 158 
#define  RESERVE 157 
#define  REZERO_UNIT 156 
#define  SEARCH_EQUAL 155 
#define  SEARCH_EQUAL_12 154 
#define  SEARCH_HIGH 153 
#define  SEARCH_HIGH_12 152 
#define  SEARCH_LOW 151 
#define  SEARCH_LOW_12 150 
#define  SEEK_10 149 
#define  SEEK_6 148 
#define  SEND_DIAGNOSTIC 147 
#define  SEND_VOLUME_TAG 146 
#define  SET_LIMITS 145 
#define  SET_WINDOW 144 
#define  SPACE 143 
#define  START_STOP 142 
#define  SYNCHRONIZE_CACHE 141 
#define  TEST_UNIT_READY 140 
#define  UPDATE_BLOCK 139 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int /*<<< orphan*/  US_DEBUGPX (char*,...) ; 
#define  VERIFY 138 
#define  WRITE_10 137 
#define  WRITE_12 136 
#define  WRITE_6 135 
#define  WRITE_BUFFER 134 
#define  WRITE_FILEMARKS 133 
#define  WRITE_LONG 132 
#define  WRITE_LONG_2 131 
#define  WRITE_SAME 130 
#define  WRITE_VERIFY 129 
#define  WRITE_VERIFY_12 128 

void usb_stor_show_command(struct scsi_cmnd *srb)
{
	char *what = NULL;
	int i;

	switch (srb->cmnd[0]) {
	case TEST_UNIT_READY: what = "TEST_UNIT_READY"; break;
	case REZERO_UNIT: what = "REZERO_UNIT"; break;
	case REQUEST_SENSE: what = "REQUEST_SENSE"; break;
	case FORMAT_UNIT: what = "FORMAT_UNIT"; break;
	case READ_BLOCK_LIMITS: what = "READ_BLOCK_LIMITS"; break;
	case REASSIGN_BLOCKS: what = "REASSIGN_BLOCKS"; break;
	case READ_6: what = "READ_6"; break;
	case WRITE_6: what = "WRITE_6"; break;
	case SEEK_6: what = "SEEK_6"; break;
	case READ_REVERSE: what = "READ_REVERSE"; break;
	case WRITE_FILEMARKS: what = "WRITE_FILEMARKS"; break;
	case SPACE: what = "SPACE"; break;
	case INQUIRY: what = "INQUIRY"; break;
	case RECOVER_BUFFERED_DATA: what = "RECOVER_BUFFERED_DATA"; break;
	case MODE_SELECT: what = "MODE_SELECT"; break;
	case RESERVE: what = "RESERVE"; break;
	case RELEASE: what = "RELEASE"; break;
	case COPY: what = "COPY"; break;
	case ERASE: what = "ERASE"; break;
	case MODE_SENSE: what = "MODE_SENSE"; break;
	case START_STOP: what = "START_STOP"; break;
	case RECEIVE_DIAGNOSTIC: what = "RECEIVE_DIAGNOSTIC"; break;
	case SEND_DIAGNOSTIC: what = "SEND_DIAGNOSTIC"; break;
	case ALLOW_MEDIUM_REMOVAL: what = "ALLOW_MEDIUM_REMOVAL"; break;
	case SET_WINDOW: what = "SET_WINDOW"; break;
	case READ_CAPACITY: what = "READ_CAPACITY"; break;
	case READ_10: what = "READ_10"; break;
	case WRITE_10: what = "WRITE_10"; break;
	case SEEK_10: what = "SEEK_10"; break;
	case WRITE_VERIFY: what = "WRITE_VERIFY"; break;
	case VERIFY: what = "VERIFY"; break;
	case SEARCH_HIGH: what = "SEARCH_HIGH"; break;
	case SEARCH_EQUAL: what = "SEARCH_EQUAL"; break;
	case SEARCH_LOW: what = "SEARCH_LOW"; break;
	case SET_LIMITS: what = "SET_LIMITS"; break;
	case READ_POSITION: what = "READ_POSITION"; break;
	case SYNCHRONIZE_CACHE: what = "SYNCHRONIZE_CACHE"; break;
	case LOCK_UNLOCK_CACHE: what = "LOCK_UNLOCK_CACHE"; break;
	case READ_DEFECT_DATA: what = "READ_DEFECT_DATA"; break;
	case MEDIUM_SCAN: what = "MEDIUM_SCAN"; break;
	case COMPARE: what = "COMPARE"; break;
	case COPY_VERIFY: what = "COPY_VERIFY"; break;
	case WRITE_BUFFER: what = "WRITE_BUFFER"; break;
	case READ_BUFFER: what = "READ_BUFFER"; break;
	case UPDATE_BLOCK: what = "UPDATE_BLOCK"; break;
	case READ_LONG: what = "READ_LONG"; break;
	case WRITE_LONG: what = "WRITE_LONG"; break;
	case CHANGE_DEFINITION: what = "CHANGE_DEFINITION"; break;
	case WRITE_SAME: what = "WRITE_SAME"; break;
	case GPCMD_READ_SUBCHANNEL: what = "READ SUBCHANNEL"; break;
	case READ_TOC: what = "READ_TOC"; break;
	case GPCMD_READ_HEADER: what = "READ HEADER"; break;
	case GPCMD_PLAY_AUDIO_10: what = "PLAY AUDIO (10)"; break;
	case GPCMD_PLAY_AUDIO_MSF: what = "PLAY AUDIO MSF"; break;
	case GPCMD_GET_EVENT_STATUS_NOTIFICATION:
		what = "GET EVENT/STATUS NOTIFICATION"; break;
	case GPCMD_PAUSE_RESUME: what = "PAUSE/RESUME"; break;
	case LOG_SELECT: what = "LOG_SELECT"; break;
	case LOG_SENSE: what = "LOG_SENSE"; break;
	case GPCMD_STOP_PLAY_SCAN: what = "STOP PLAY/SCAN"; break;
	case GPCMD_READ_DISC_INFO: what = "READ DISC INFORMATION"; break;
	case GPCMD_READ_TRACK_RZONE_INFO:
		what = "READ TRACK INFORMATION"; break;
	case GPCMD_RESERVE_RZONE_TRACK: what = "RESERVE TRACK"; break;
	case GPCMD_SEND_OPC: what = "SEND OPC"; break;
	case MODE_SELECT_10: what = "MODE_SELECT_10"; break;
	case GPCMD_REPAIR_RZONE_TRACK: what = "REPAIR TRACK"; break;
	case 0x59: what = "READ MASTER CUE"; break;
	case MODE_SENSE_10: what = "MODE_SENSE_10"; break;
	case GPCMD_CLOSE_TRACK: what = "CLOSE TRACK/SESSION"; break;
	case 0x5C: what = "READ BUFFER CAPACITY"; break;
	case 0x5D: what = "SEND CUE SHEET"; break;
	case GPCMD_BLANK: what = "BLANK"; break;
	case REPORT_LUNS: what = "REPORT LUNS"; break;
	case MOVE_MEDIUM: what = "MOVE_MEDIUM or PLAY AUDIO (12)"; break;
	case READ_12: what = "READ_12"; break;
	case WRITE_12: what = "WRITE_12"; break;
	case WRITE_VERIFY_12: what = "WRITE_VERIFY_12"; break;
	case SEARCH_HIGH_12: what = "SEARCH_HIGH_12"; break;
	case SEARCH_EQUAL_12: what = "SEARCH_EQUAL_12"; break;
	case SEARCH_LOW_12: what = "SEARCH_LOW_12"; break;
	case SEND_VOLUME_TAG: what = "SEND_VOLUME_TAG"; break;
	case READ_ELEMENT_STATUS: what = "READ_ELEMENT_STATUS"; break;
	case GPCMD_READ_CD_MSF: what = "READ CD MSF"; break;
	case GPCMD_SCAN: what = "SCAN"; break;
	case GPCMD_SET_SPEED: what = "SET CD SPEED"; break;
	case GPCMD_MECHANISM_STATUS: what = "MECHANISM STATUS"; break;
	case GPCMD_READ_CD: what = "READ CD"; break;
	case 0xE1: what = "WRITE CONTINUE"; break;
	case WRITE_LONG_2: what = "WRITE_LONG_2"; break;
	default: what = "(unknown command)"; break;
	}
	US_DEBUGP("Command %s (%d bytes)\n", what, srb->cmd_len);
	US_DEBUGP("");
	for (i = 0; i < srb->cmd_len && i < 16; i++)
		US_DEBUGPX(" %02x", srb->cmnd[i]);
	US_DEBUGPX("\n");
}