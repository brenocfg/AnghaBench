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
typedef  scalar_t__ UBYTE ;

/* Variables and functions */
#define  BINLOAD_LOADING_BASIC_LISTED 134 
#define  BINLOAD_LOADING_BASIC_LISTED_ATARI 133 
#define  BINLOAD_LOADING_BASIC_LISTED_CR 132 
#define  BINLOAD_LOADING_BASIC_LISTED_CRLF 131 
#define  BINLOAD_LOADING_BASIC_LISTED_CR_OR_CRLF 130 
#define  BINLOAD_LOADING_BASIC_LISTED_LF 129 
#define  BINLOAD_LOADING_BASIC_SAVED 128 
 int /*<<< orphan*/ * BINLOAD_bin_file ; 
 int BINLOAD_loading_basic ; 
 int /*<<< orphan*/  CPU_ClrN ; 
 int /*<<< orphan*/  CPU_SetN ; 
 scalar_t__ CPU_regA ; 
 int CPU_regY ; 
 int EOF ; 
 int fgetc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Devices_ReadBasicFile(void)
{
	if (BINLOAD_bin_file != NULL) {
		int ch = fgetc(BINLOAD_bin_file);
		if (ch == EOF) {
			CPU_regY = 136;
			CPU_SetN;
			return;
		}
		switch (BINLOAD_loading_basic) {
		case BINLOAD_LOADING_BASIC_LISTED:
			switch (ch) {
			case 0x9b:
				BINLOAD_loading_basic = BINLOAD_LOADING_BASIC_LISTED_ATARI;
				break;
			case 0x0a:
				BINLOAD_loading_basic = BINLOAD_LOADING_BASIC_LISTED_LF;
				ch = 0x9b;
				break;
			case 0x0d:
				BINLOAD_loading_basic = BINLOAD_LOADING_BASIC_LISTED_CR_OR_CRLF;
				ch = 0x9b;
				break;
			default:
				break;
			}
			break;
		case BINLOAD_LOADING_BASIC_LISTED_CR:
			if (ch == 0x0d)
				ch = 0x9b;
			break;
		case BINLOAD_LOADING_BASIC_LISTED_LF:
			if (ch == 0x0a)
				ch = 0x9b;
			break;
		case BINLOAD_LOADING_BASIC_LISTED_CRLF:
			if (ch == 0x0a) {
				ch = fgetc(BINLOAD_bin_file);
				if (ch == EOF) {
					CPU_regY = 136;
					CPU_SetN;
					return;
				}
			}
			if (ch == 0x0d)
				ch = 0x9b;
			break;
		case BINLOAD_LOADING_BASIC_LISTED_CR_OR_CRLF:
			if (ch == 0x0a) {
				BINLOAD_loading_basic = BINLOAD_LOADING_BASIC_LISTED_CRLF;
				ch = fgetc(BINLOAD_bin_file);
				if (ch == EOF) {
					CPU_regY = 136;
					CPU_SetN;
					return;
				}
			}
			else
				BINLOAD_loading_basic = BINLOAD_LOADING_BASIC_LISTED_CR;
			if (ch == 0x0d)
				ch = 0x9b;
			break;
		case BINLOAD_LOADING_BASIC_SAVED:
		case BINLOAD_LOADING_BASIC_LISTED_ATARI:
		default:
			break;
		}
		CPU_regA = (UBYTE) ch;
		CPU_regY = 1;
		CPU_ClrN;
	}
}