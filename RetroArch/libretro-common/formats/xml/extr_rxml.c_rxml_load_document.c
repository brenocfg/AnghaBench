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
typedef  int /*<<< orphan*/  rxml_document_t ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 long filestream_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t filestream_read (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (long) ; 
 int /*<<< orphan*/ * rxml_load_document_string (char*) ; 

rxml_document_t *rxml_load_document(const char *path)
{
   rxml_document_t *doc;
   char *memory_buffer     = NULL;
   long len                = 0;
   RFILE *file             = filestream_open(path,
         RETRO_VFS_FILE_ACCESS_READ,
         RETRO_VFS_FILE_ACCESS_HINT_NONE);
   if (!file)
      return NULL;

   len           = filestream_get_size(file);
   memory_buffer = (char*)malloc(len + 1);
   if (!memory_buffer)
      goto error;

   memory_buffer[len] = '\0';
   if (filestream_read(file, memory_buffer, len) != (size_t)len)
      goto error;

   filestream_close(file);
   file = NULL;

   doc = rxml_load_document_string(memory_buffer);

   free(memory_buffer);
   return doc;

error:
   free(memory_buffer);
   if(file)
      filestream_close(file);
   return NULL;
}