#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; } ;
typedef  scalar_t__ ULONG ;
struct TYPE_2__ {int size; scalar_t__ crc32; int /*<<< orphan*/  filename; scalar_t__ unset; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  CRC32_FromFile (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ CRC_NULL ; 
 int /*<<< orphan*/  ClearUnsetFlag (int) ; 
 int FALSE ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  IsLengthAllowed (int) ; 
 int MatchByName (char*,int,int) ; 
 int SYSROM_SIZE ; 
 TYPE_1__* SYSROM_roms ; 
 int TRUE ; 
 int /*<<< orphan*/  Util_catpath (char*,char const*,char*) ; 
 int Util_flen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Util_rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ num_unset_roms ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tolower (char) ; 

int SYSROM_FindInDir(char const *directory, int only_if_not_set)
{
	DIR *dir;
	struct dirent *entry;

	if (only_if_not_set && num_unset_roms == 0)
		/* No unset ROM paths left. */
		return TRUE;

	if ((dir = opendir(directory)) == NULL)
		return FALSE;

	while ((entry = readdir(dir)) != NULL) {
		char full_filename[FILENAME_MAX];
		FILE *file;
		int len;
		int id;
		ULONG crc;
		int matched_crc = FALSE;
		Util_catpath(full_filename, directory, entry->d_name);
		if ((file = fopen(full_filename, "rb")) == NULL)
			/* Ignore non-readable files (e.g. directories). */
			continue;

		len = Util_flen(file);
		/* Don't proceed to CRC computation if the file has invalid size. */
		if (!IsLengthAllowed(len)){
			fclose(file);
			continue;
		}
		Util_rewind(file);

		if (!CRC32_FromFile(file, &crc)) {
			fclose(file);
			continue;
		}
		fclose(file);

		/* Match ROM image by CRC. */
		for (id = 0; id < SYSROM_SIZE; ++id) {
			if ((!only_if_not_set || SYSROM_roms[id].unset)
			    && SYSROM_roms[id].size == len
			    && SYSROM_roms[id].crc32 != CRC_NULL && SYSROM_roms[id].crc32 == crc) {
				strcpy(SYSROM_roms[id].filename, full_filename);
				ClearUnsetFlag(id);
				matched_crc = TRUE;
				break;
			}
		}

		if (!matched_crc) {
			/* Match custom ROM image by name. */
			char *c = entry->d_name;
			while (*c != 0) {
				*c = (char)tolower(*c);
				++c;
			}

			id = MatchByName(entry->d_name, len, only_if_not_set);
			if (id >= 0){
				strcpy(SYSROM_roms[id].filename, full_filename);
				ClearUnsetFlag(id);
			}
		}
	}

	closedir(dir);
	return TRUE;
}