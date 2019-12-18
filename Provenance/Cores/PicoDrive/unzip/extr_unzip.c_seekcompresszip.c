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
struct zipent {long offset_lcl_hdr_frm_frst_disk; } ;
struct TYPE_4__ {int /*<<< orphan*/  zip; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ ZIP ;
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_CORRUPT ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int ZIPFNLN ; 
 int ZIPNAME ; 
 int ZIPXTRALN ; 
 int /*<<< orphan*/  errormsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int read_word (char*) ; 
 int /*<<< orphan*/  revivezip (TYPE_1__*) ; 

int seekcompresszip(ZIP* zip, struct zipent* ent) {
	char buf[ZIPNAME];
	long offset;

	if (!zip->fp) {
		if (!revivezip(zip))
			return -1;
	}

	if (fseek(zip->fp, ent->offset_lcl_hdr_frm_frst_disk, SEEK_SET)!=0) {
		errormsg ("Seeking to header", ERROR_CORRUPT, zip->zip);
		return -1;
	}

	if (fread(buf, ZIPNAME, 1, zip->fp)!=1) {
		errormsg ("Reading header", ERROR_CORRUPT, zip->zip);
		return -1;
	}

	{
		UINT16 filename_length = read_word (buf+ZIPFNLN);
		UINT16 extra_field_length = read_word (buf+ZIPXTRALN);

		/* calculate offset to data and fseek() there */
		offset = ent->offset_lcl_hdr_frm_frst_disk + ZIPNAME + filename_length + extra_field_length;

		if (fseek(zip->fp, offset, SEEK_SET) != 0) {
			errormsg ("Seeking to compressed data", ERROR_CORRUPT, zip->zip);
			return -1;
		}

	}

	return 0;
}