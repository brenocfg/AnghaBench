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
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_plist_parse (char*,size_t) ; 
 char* malloc (size_t) ; 

hb_value_t*
hb_plist_parse_file(const char *filename)
{
    char *buffer;
    size_t size;
    hb_value_t *gval;
    FILE *fd;

    fd = fopen(filename, "r");
    if (fd == NULL)
    {
        // File doesn't exist
        return NULL;
    }
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    buffer = malloc(size+1);
    size = fread(buffer, 1, size, fd);
    buffer[size] = 0;
    gval = hb_plist_parse(buffer, size);
    free(buffer);
    fclose(fd);
    return gval;
}