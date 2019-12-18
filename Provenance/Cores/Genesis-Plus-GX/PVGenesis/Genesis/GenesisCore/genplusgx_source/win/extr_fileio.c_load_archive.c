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
typedef  int /*<<< orphan*/  gzFile ;

/* Variables and functions */
 int UNZ_OK ; 
 scalar_t__ check_zip (char*) ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gzopen (char*,char*) ; 
 int gzread (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int unzClose (int /*<<< orphan*/ *) ; 
 int unzCloseCurrentFile (int /*<<< orphan*/ *) ; 
 int unzGetCurrentFileInfo (int /*<<< orphan*/ *,TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int unzGoToFirstFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * unzOpen (char*) ; 
 int unzOpenCurrentFile (int /*<<< orphan*/ *) ; 
 int unzReadCurrentFile (int /*<<< orphan*/ *,unsigned char*,int) ; 

int load_archive(char *filename, unsigned char *buffer, int maxsize, char *extension)
{
  int size = 0;
  
  if(check_zip(filename))
  {
    unz_file_info info;
    int ret = 0;
    char fname[256];

    /* Attempt to open the archive */
    unzFile *fd = unzOpen(filename);
    if (!fd) return 0;

    /* Go to first file in archive */
    ret = unzGoToFirstFile(fd);
    if(ret != UNZ_OK)
    {
      unzClose(fd);
      return 0;
    }

    /* Get file informations and update filename */
    ret = unzGetCurrentFileInfo(fd, &info, fname, 256, NULL, 0, NULL, 0);
    if(ret != UNZ_OK)
    {
      unzClose(fd);
      return 0;
    }

    /* Compressed filename extension */
    if (extension)
    {
      strncpy(extension, &fname[strlen(fname) - 3], 3);
      extension[3] = 0;
    }

    /* Open the file for reading */
    ret = unzOpenCurrentFile(fd);
    if(ret != UNZ_OK)
    {
      unzClose(fd);
      return 0;
    }

    /* Retrieve uncompressed file size */
    size = info.uncompressed_size;
    if(size > maxsize)
    {
      size = maxsize;
    }

    /* Read (decompress) the file */
    ret = unzReadCurrentFile(fd, buffer, size);
    if(ret != size)
    {
      unzCloseCurrentFile(fd);
      unzClose(fd);
      return 0;
    }

    /* Close the current file */
    ret = unzCloseCurrentFile(fd);
    if(ret != UNZ_OK)
    {
      unzClose(fd);
      return 0;
    }

    /* Close the archive */
    ret = unzClose(fd);
    if(ret != UNZ_OK) return 0;
  }
  else
  {
    /* Open file */
    gzFile *gd = gzopen(filename, "rb");
    if (!gd) return 0;

    /* Read file data */
    size = gzread(gd, buffer, maxsize);

    /* filename extension */
    if (extension)
    {
      strncpy(extension, &filename[strlen(filename) - 3], 3);
      extension[3] = 0;
    }

    /* Close file */
    gzclose(gd);
  }

  /* Return loaded ROM size */
  return size;
}