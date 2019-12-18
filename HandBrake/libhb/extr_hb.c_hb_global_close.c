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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* hb_get_temporary_directory () ; 
 int /*<<< orphan*/  hb_presets_free () ; 
 char* hb_strdup_printf (char*,char*,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void hb_global_close()
{
    char          * dirname;
    DIR           * dir;
    struct dirent * entry;

    hb_presets_free();

    /* Find and remove temp folder */
    dirname = hb_get_temporary_directory();

    dir = opendir( dirname );
    if (dir)
    {
        while( ( entry = readdir( dir ) ) )
        {
            char * filename;
            if( entry->d_name[0] == '.' )
            {
                continue;
            }
            filename = hb_strdup_printf("%s/%s", dirname, entry->d_name);
            unlink( filename );
            free(filename);
        }
        closedir( dir );
        rmdir( dirname );
    }
    free(dirname);
}