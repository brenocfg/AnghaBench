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
typedef  int /*<<< orphan*/  gssize ;
typedef  scalar_t__ gchar ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 size_t fread (scalar_t__*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_fopen (scalar_t__ const*,char*) ; 
 int /*<<< orphan*/  g_free (scalar_t__*) ; 
 scalar_t__* g_malloc (size_t) ; 
 int /*<<< orphan*/  g_warning (char*,scalar_t__ const*) ; 
 int /*<<< orphan*/ * ghb_plist_parse (scalar_t__*,int /*<<< orphan*/ ) ; 

GhbValue*
ghb_plist_parse_file(const gchar *filename)
{
    gchar *buffer;
    size_t size;
    GhbValue *gval;
    FILE *fd;

    fd = g_fopen(filename, "r");
    if (fd == NULL)
    {
        g_warning("Plist parse: failed to open %s", filename);
        return NULL;
    }
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    buffer = g_malloc(size+1);
    size = fread(buffer, 1, size, fd);
    buffer[size] = 0;
    gval = ghb_plist_parse(buffer, (gssize)size);
    g_free(buffer);
    fclose(fd);
    return gval;
}