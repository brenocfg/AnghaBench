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
typedef  char UBYTE ;
struct TYPE_4__ {char const* filename; char* image; int type; int size; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ CARTRIDGE_image_t ;

/* Variables and functions */
 int CARTRIDGE_BAD_CHECKSUM ; 
 int CARTRIDGE_BAD_FORMAT ; 
 int CARTRIDGE_CANT_OPEN ; 
 int CARTRIDGE_Checksum (char*,int) ; 
 int CARTRIDGE_LAST_SUPPORTED ; 
 int CARTRIDGE_NONE ; 
 int CARTRIDGE_UNKNOWN ; 
 int* CARTRIDGE_kb ; 
 int /*<<< orphan*/  InitCartridge (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int Util_flen (int /*<<< orphan*/ *) ; 
 scalar_t__ Util_malloc (int) ; 
 int /*<<< orphan*/  Util_rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcpy (char const*,char const*) ; 

__attribute__((used)) static int InsertCartridge(const char *filename, CARTRIDGE_image_t *cart)
{
	FILE *fp;
	int len;
	int type;
	UBYTE header[16];

	/* open file */
	fp = fopen(filename, "rb");
	if (fp == NULL)
		return CARTRIDGE_CANT_OPEN;
	/* check file length */
	len = Util_flen(fp);
	Util_rewind(fp);

	/* Guard against providing cart->filename as parameter. */
	if (cart->filename != filename)
		/* Save Filename for state save */
		strcpy(cart->filename, filename);

	/* if full kilobytes, assume it is raw image */
	if ((len & 0x3ff) == 0) {
		/* alloc memory and read data */
		cart->image = (UBYTE *) Util_malloc(len);
		if (fread(cart->image, 1, len, fp) < len) {
			Log_print("Error reading cartridge.\n");
		}
		fclose(fp);
		/* find cart type */
		cart->type = CARTRIDGE_NONE;
		len >>= 10;	/* number of kilobytes */
		cart->size = len;
		for (type = 1; type <= CARTRIDGE_LAST_SUPPORTED; type++)
			if (CARTRIDGE_kb[type] == len) {
				if (cart->type == CARTRIDGE_NONE) {
					cart->type = type;
				} else {
					/* more than one cartridge type of such length - user must select */
					cart->type = CARTRIDGE_UNKNOWN;
					return len;
				}
			}
		if (cart->type != CARTRIDGE_NONE) {
			InitCartridge(cart);
			return 0;	/* ok */
		}
		free(cart->image);
		cart->image = NULL;
		return CARTRIDGE_BAD_FORMAT;
	}
	/* if not full kilobytes, assume it is CART file */
	if (fread(header, 1, 16, fp) < 16) {
		Log_print("Error reading cartridge.\n");
	}
	if ((header[0] == 'C') &&
		(header[1] == 'A') &&
		(header[2] == 'R') &&
		(header[3] == 'T')) {
		type = (header[4] << 24) |
			(header[5] << 16) |
			(header[6] << 8) |
			header[7];
		if (type >= 1 && type <= CARTRIDGE_LAST_SUPPORTED) {
			int checksum;
			int result;
			len = CARTRIDGE_kb[type] << 10;
			cart->size = CARTRIDGE_kb[type];
			/* alloc memory and read data */
			cart->image = (UBYTE *) Util_malloc(len);
			if (fread(cart->image, 1, len, fp) < len) {
				Log_print("Error reading cartridge.\n");
			}
			fclose(fp);
			checksum = (header[8] << 24) |
				(header[9] << 16) |
				(header[10] << 8) |
				header[11];
			cart->type = type;
			result = checksum == CARTRIDGE_Checksum(cart->image, len) ? 0 : CARTRIDGE_BAD_CHECKSUM;
			InitCartridge(cart);
			return result;
		}
	}
	fclose(fp);
	return CARTRIDGE_BAD_FORMAT;
}