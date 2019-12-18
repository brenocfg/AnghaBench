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
typedef  int /*<<< orphan*/  datadir_t ;

/* Variables and functions */
#define  CHANGE_DEFINITION 156 
#define  COMPARE 155 
#define  COPY 154 
#define  COPY_VERIFY 153 
 int /*<<< orphan*/  DATADIR_IN ; 
 int /*<<< orphan*/  DATADIR_OUT ; 
#define  FORMAT_UNIT 152 
#define  LOG_SELECT 151 
#define  MEDIUM_SCAN 150 
#define  MODE_SELECT 149 
#define  MODE_SELECT_10 148 
#define  REASSIGN_BLOCKS 147 
#define  RESERVE 146 
#define  SEARCH_EQUAL 145 
#define  SEARCH_EQUAL_12 144 
#define  SEARCH_HIGH 143 
#define  SEARCH_HIGH_12 142 
#define  SEARCH_LOW 141 
#define  SEARCH_LOW_12 140 
#define  SEND_DIAGNOSTIC 139 
#define  SEND_VOLUME_TAG 138 
#define  SET_WINDOW 137 
#define  UPDATE_BLOCK 136 
#define  WRITE_10 135 
#define  WRITE_12 134 
#define  WRITE_6 133 
#define  WRITE_BUFFER 132 
#define  WRITE_LONG 131 
#define  WRITE_SAME 130 
#define  WRITE_VERIFY 129 
#define  WRITE_VERIFY_12 128 

__attribute__((used)) static
datadir_t acornscsi_datadirection(int command)
{
    switch (command) {
    case CHANGE_DEFINITION:	case COMPARE:		case COPY:
    case COPY_VERIFY:		case LOG_SELECT:	case MODE_SELECT:
    case MODE_SELECT_10:	case SEND_DIAGNOSTIC:	case WRITE_BUFFER:
    case FORMAT_UNIT:		case REASSIGN_BLOCKS:	case RESERVE:
    case SEARCH_EQUAL:		case SEARCH_HIGH:	case SEARCH_LOW:
    case WRITE_6:		case WRITE_10:		case WRITE_VERIFY:
    case UPDATE_BLOCK:		case WRITE_LONG:	case WRITE_SAME:
    case SEARCH_HIGH_12:	case SEARCH_EQUAL_12:	case SEARCH_LOW_12:
    case WRITE_12:		case WRITE_VERIFY_12:	case SET_WINDOW:
    case MEDIUM_SCAN:		case SEND_VOLUME_TAG:	case 0xea:
	return DATADIR_OUT;
    default:
	return DATADIR_IN;
    }
}