#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int uncompressed_size; } ;
typedef  TYPE_1__ unz_file_info ;
typedef  int /*<<< orphan*/  unzFile ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  gzFile ;

/* Variables and functions */
 int UNZ_OK ; 
 scalar_t__ check_zip (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gzopen (char*,char*) ; 
 int /*<<< orphan*/  gzread (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int gzsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int unzClose (int /*<<< orphan*/ *) ; 
 int unzCloseCurrentFile (int /*<<< orphan*/ *) ; 
 int unzGetCurrentFileInfo (int /*<<< orphan*/ *,TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int unzGoToFirstFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * unzOpen (char*) ; 
 int unzOpenCurrentFile (int /*<<< orphan*/ *) ; 
 int unzReadCurrentFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

uint8 *load_archive(char *filename, int *file_size)
{
    int size = 0;
    uint8 *buf = NULL;

    if(check_zip(filename))
    {
        unzFile *fd = NULL;
        unz_file_info info;
        int ret = 0;

        /* Attempt to open the archive */
        fd = unzOpen(filename);
        if(!fd) return (NULL);

        /* Go to first file in archive */
        ret = unzGoToFirstFile(fd);
        if(ret != UNZ_OK)
        {
            unzClose(fd);
            return (NULL);
        }

        ret = unzGetCurrentFileInfo(fd, &info, filename, 128, NULL, 0, NULL, 0);
        if(ret != UNZ_OK)
        {
            unzClose(fd);
            return (NULL);
        }

        /* Open the file for reading */
        ret = unzOpenCurrentFile(fd);
        if(ret != UNZ_OK)
        {
            unzClose(fd);
            return (NULL);
        }

        /* Allocate file data buffer */
        size = info.uncompressed_size;
        buf = malloc(size);
        if(!buf)
        {
            unzClose(fd);
            return (NULL);
        }

        /* Read (decompress) the file */
        ret = unzReadCurrentFile(fd, buf, info.uncompressed_size);
        if(ret != info.uncompressed_size)
        {
            free(buf);
            unzCloseCurrentFile(fd);
            unzClose(fd);
            return (NULL);
        }

        /* Close the current file */
        ret = unzCloseCurrentFile(fd);
        if(ret != UNZ_OK)
        {
            free(buf);
            unzClose(fd);
            return (NULL);
        }

        /* Close the archive */
        ret = unzClose(fd);
        if(ret != UNZ_OK)
        {
            free(buf);
            return (NULL);
        }

        /* Update file size and return pointer to file data */
        *file_size = size;
        return (buf);
    }
    else
    {
        gzFile *gd = NULL;

        /* Open file */
        gd = gzopen(filename, "rb");
        if(!gd) return (0);

        /* Get file size */
        size = gzsize(gd);

        /* Allocate file data buffer */
        buf = malloc(size);
        if(!buf)
        {
            gzclose(gd);
            return (0);
        }

        /* Read file data */
        gzread(gd, buf, size);

        /* Close file */
        gzclose(gd);

        /* Update file size and return pointer to file data */
        *file_size = size;
        return (buf);
    }
}