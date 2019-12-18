#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sector_buf ;
typedef  int UBYTE ;
struct TYPE_5__ {int current_sector; int sectorsize; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ ATR_Info ;

/* Variables and functions */
 int EOF ; 
 int FALSE ; 
 int /*<<< orphan*/  Log_print (char*,int,...) ; 
 int TRUE ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int fgetw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fload (int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  pad_till_sector (TYPE_1__*,int) ; 
 int /*<<< orphan*/  write_atr_sector (TYPE_1__*,int*) ; 

__attribute__((used)) static int dcm_pass(FILE *infp, ATR_Info *pai)
{
	UBYTE sector_buf[256];
	memset(sector_buf, 0, sizeof(sector_buf));
	for (;;) {
		/* sector group */
		int sector_no;
		int sector_type;
		sector_no = fgetw(infp);
		sector_type = fgetc(infp);
		if (sector_type == 0x45)
			return TRUE;
		if (sector_no < pai->current_sector) {
			Log_print("Error: current sector is %d, next sector group at %d", pai->current_sector, sector_no);
			return FALSE;
		}
		if (!pad_till_sector(pai, sector_no))
			return FALSE;
		for (;;) {
			/* sector */
			int i;
			switch (sector_type & 0x7f) {
			case 0x41:
				i = fgetc(infp);
				if (i == EOF)
					return FALSE;
				do {
					int b = fgetc(infp);
					if (b == EOF)
						return FALSE;
					sector_buf[i] = (UBYTE) b;
				} while (i-- != 0);
				break;
			case 0x42:
				if (!fload(sector_buf + 123, 5, infp))
					return FALSE;
				memset(sector_buf, sector_buf[123], 123);
				break;
			case 0x43:
				i = 0;
				do {
					int j;
					int c;
					j = fgetc(infp);
					if (j < i) {
						if (j != 0)
							return FALSE;
						j = 256;
					}
					if (i < j && !fload(sector_buf + i, j - i, infp))
						return FALSE;
					if (j >= pai->sectorsize)
						break;
					i = fgetc(infp);
					if (i < j) {
						if (i != 0)
							return FALSE;
						i = 256;
					}
					c = fgetc(infp);
					if (c == EOF)
						return FALSE;
					memset(sector_buf + j, c, i - j);
				} while (i < pai->sectorsize);
				break;
			case 0x44:
				i = fgetc(infp);
				if (i == EOF || i >= pai->sectorsize)
					return FALSE;
				if (!fload(sector_buf + i, pai->sectorsize - i, infp))
					return FALSE;
				break;
			case 0x46:
				break;
			case 0x47:
				if (!fload(sector_buf, pai->sectorsize, infp))
					return FALSE;
				break;
			default:
				Log_print("Unrecognized sector coding type 0x%02X", sector_type);
				return FALSE;
			}
			if (!write_atr_sector(pai, sector_buf))
				return FALSE;
			if (!(sector_type & 0x80))
				break; /* goto sector group */
			sector_type = fgetc(infp);
			if (sector_type == 0x45)
				return TRUE;
		}
	}
}