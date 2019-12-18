#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ info_level; scalar_t__ unicode; } ;
struct cifsFileInfo {TYPE_1__ srch_inf; } ;
typedef  scalar_t__ __le16 ;
struct TYPE_14__ {char* FileName; int /*<<< orphan*/  FileNameLength; } ;
struct TYPE_13__ {char* FileName; int /*<<< orphan*/  FileNameLength; } ;
struct TYPE_12__ {char* FileName; int /*<<< orphan*/  FileNameLength; } ;
struct TYPE_11__ {char* FileName; } ;
struct TYPE_10__ {char* FileName; int FileNameLength; } ;
struct TYPE_9__ {char* FileName; int /*<<< orphan*/  FileNameLength; } ;
typedef  TYPE_2__ SEARCH_ID_FULL_DIR_INFO ;
typedef  TYPE_3__ FIND_FILE_STANDARD_INFO ;
typedef  TYPE_4__ FILE_UNIX_INFO ;
typedef  TYPE_5__ FILE_FULL_DIRECTORY_INFO ;
typedef  TYPE_6__ FILE_DIRECTORY_INFO ;
typedef  TYPE_7__ FILE_BOTH_DIRECTORY_INFO ;

/* Variables and functions */
 scalar_t__ SMB_FIND_FILE_BOTH_DIRECTORY_INFO ; 
 scalar_t__ SMB_FIND_FILE_DIRECTORY_INFO ; 
 scalar_t__ SMB_FIND_FILE_FULL_DIRECTORY_INFO ; 
 scalar_t__ SMB_FIND_FILE_ID_FULL_DIR_INFO ; 
 scalar_t__ SMB_FIND_FILE_INFO_STANDARD ; 
 scalar_t__ SMB_FIND_FILE_UNIX ; 
 scalar_t__ UNICODE_DOT ; 
 int /*<<< orphan*/  cFYI (int,char*,scalar_t__) ; 
 int cifs_unicode_bytelen (char*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int strnlen (char*,int) ; 

__attribute__((used)) static int cifs_entry_is_dot(char *current_entry, struct cifsFileInfo *cfile)
{
	int rc = 0;
	char *filename = NULL;
	int len = 0;

	if (cfile->srch_inf.info_level == SMB_FIND_FILE_UNIX) {
		FILE_UNIX_INFO *pFindData = (FILE_UNIX_INFO *)current_entry;
		filename = &pFindData->FileName[0];
		if (cfile->srch_inf.unicode) {
			len = cifs_unicode_bytelen(filename);
		} else {
			/* BB should we make this strnlen of PATH_MAX? */
			len = strnlen(filename, 5);
		}
	} else if (cfile->srch_inf.info_level == SMB_FIND_FILE_DIRECTORY_INFO) {
		FILE_DIRECTORY_INFO *pFindData =
			(FILE_DIRECTORY_INFO *)current_entry;
		filename = &pFindData->FileName[0];
		len = le32_to_cpu(pFindData->FileNameLength);
	} else if (cfile->srch_inf.info_level ==
			SMB_FIND_FILE_FULL_DIRECTORY_INFO) {
		FILE_FULL_DIRECTORY_INFO *pFindData =
			(FILE_FULL_DIRECTORY_INFO *)current_entry;
		filename = &pFindData->FileName[0];
		len = le32_to_cpu(pFindData->FileNameLength);
	} else if (cfile->srch_inf.info_level ==
			SMB_FIND_FILE_ID_FULL_DIR_INFO) {
		SEARCH_ID_FULL_DIR_INFO *pFindData =
			(SEARCH_ID_FULL_DIR_INFO *)current_entry;
		filename = &pFindData->FileName[0];
		len = le32_to_cpu(pFindData->FileNameLength);
	} else if (cfile->srch_inf.info_level ==
			SMB_FIND_FILE_BOTH_DIRECTORY_INFO) {
		FILE_BOTH_DIRECTORY_INFO *pFindData =
			(FILE_BOTH_DIRECTORY_INFO *)current_entry;
		filename = &pFindData->FileName[0];
		len = le32_to_cpu(pFindData->FileNameLength);
	} else if (cfile->srch_inf.info_level == SMB_FIND_FILE_INFO_STANDARD) {
		FIND_FILE_STANDARD_INFO *pFindData =
			(FIND_FILE_STANDARD_INFO *)current_entry;
		filename = &pFindData->FileName[0];
		len = pFindData->FileNameLength;
	} else {
		cFYI(1, "Unknown findfirst level %d",
			 cfile->srch_inf.info_level);
	}

	if (filename) {
		if (cfile->srch_inf.unicode) {
			__le16 *ufilename = (__le16 *)filename;
			if (len == 2) {
				/* check for . */
				if (ufilename[0] == UNICODE_DOT)
					rc = 1;
			} else if (len == 4) {
				/* check for .. */
				if ((ufilename[0] == UNICODE_DOT)
				   && (ufilename[1] == UNICODE_DOT))
					rc = 2;
			}
		} else /* ASCII */ {
			if (len == 1) {
				if (filename[0] == '.')
					rc = 1;
			} else if (len == 2) {
				if ((filename[0] == '.') && (filename[1] == '.'))
					rc = 2;
			}
		}
	}

	return rc;
}