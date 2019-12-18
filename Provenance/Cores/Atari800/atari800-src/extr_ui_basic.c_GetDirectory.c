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
struct stat {int st_mode; } ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ BasicUIOpenDir (char const*) ; 
 scalar_t__ BasicUIReadDir (char*,int*) ; 
 int FILENAMES_INITIAL_SIZE ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  FilenamesAdd (char*) ; 
 int /*<<< orphan*/  FilenamesSort (char const**,char const**) ; 
 int GetLogicalDrives () ; 
 int /*<<< orphan*/  Log_print (char*,char const*) ; 
 int S_IXUSR ; 
 scalar_t__ Util_malloc (size_t) ; 
 char* Util_strdup (char*) ; 
 unsigned short _STAT_DIRSIZE ; 
 unsigned short _STAT_EXEC_EXT ; 
 unsigned short _STAT_EXEC_MAGIC ; 
 unsigned short _STAT_INODE ; 
 unsigned short _STAT_ROOT_TIME ; 
 unsigned short _STAT_WRITEBIT ; 
 unsigned short _djstat_flags ; 
 char const** filenames ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int n_filenames ; 
 scalar_t__ stat (char*,struct stat*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void GetDirectory(const char *directory)
{
#ifdef __DJGPP__
	unsigned short s_backup = _djstat_flags;
	_djstat_flags = _STAT_INODE | _STAT_EXEC_EXT | _STAT_EXEC_MAGIC | _STAT_DIRSIZE |
		_STAT_ROOT_TIME | _STAT_WRITEBIT;
	/* we do not need any of those 'hard-to-get' informations */
#endif	/* DJGPP */

	filenames = (const char **) Util_malloc(FILENAMES_INITIAL_SIZE * sizeof(const char *));
	n_filenames = 0;

	if (BasicUIOpenDir(directory)) {
		char filename[FILENAME_MAX];
		int isdir;

		while (BasicUIReadDir(filename, &isdir)) {
			char *filename2;

			if (filename[0] == '\0' ||
				(filename[0] == '.' && filename[1] == '\0'))
				continue;

			if (isdir) {
				/* add directories as [dir] */
				size_t len = strlen(filename);
				filename2 = (char *) Util_malloc(len + 3);
				memcpy(filename2 + 1, filename, len);
				filename2[0] = '[';
				filename2[len + 1] = ']';
				filename2[len + 2] = '\0';
			}
			else
				filename2 = Util_strdup(filename);

			FilenamesAdd(filename2);
		}

		FilenamesSort(filenames, filenames + n_filenames);
	}
	else {
		Log_print("Error opening '%s' directory", directory);
	}
#ifdef PS2
	FilenamesAdd(Util_strdup("[mc0:]"));
#endif
#ifdef DOS_DRIVES
	/* in DOS/Windows, add all existing disk letters */
	{
		char letter;
#ifdef HAVE_WINDOWS_H
		DWORD drive_mask = GetLogicalDrives();
		for (letter = 'A'; letter <= 'Z'; letter++) {
			if (drive_mask & 1) {
				static char drive2[5] = "[C:]";
				drive2[1] = letter;
				FilenamesAdd(Util_strdup(drive2));
			}
			drive_mask >>= 1;
		}
#else /* HAVE_WINDOWS_H */
		for (letter = 'A'; letter <= 'Z'; letter++) {
#ifdef __DJGPP__
			static char drive[3] = "C:";
			struct stat st;
			drive[0] = letter;
			/* don't check floppies - it's slow */
			if (letter < 'C' || (stat(drive, &st) == 0 && (st.st_mode & S_IXUSR) != 0))
#endif /* __DJGPP__ */
			{
				static char drive2[5] = "[C:]";
				drive2[1] = letter;
				FilenamesAdd(Util_strdup(drive2));
			}
		}
#endif /* HAVE_WINDOWS_H */
	}
#endif /* DOS_DRIVES */
#ifdef __DJGPP__
	_djstat_flags = s_backup;	/* restore the original state */
#endif
}