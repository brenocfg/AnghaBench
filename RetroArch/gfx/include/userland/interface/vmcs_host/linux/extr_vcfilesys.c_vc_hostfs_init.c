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
typedef  int /*<<< orphan*/  file_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MINOR (char*) ; 
 int /*<<< orphan*/  FILE_INFO_TABLE_CHUNK_LEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  file_info_table_len ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  hostfs_log_cat ; 
 int /*<<< orphan*/ * p_file_info_table ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_current () ; 
 char* vcos_thread_get_name (int /*<<< orphan*/ ) ; 

void vc_hostfs_init(void)
{
   // This hostfs module is not thread safe - it allocaes a block
   // of memory and uses it without any kind of locking.
   //
   // It offers no advantage of stdio, and so most clients should
   // not use it. Arguably FILESYS should use it in order to get
   // the FIFO support.

   const char *thread_name = vcos_thread_get_name(vcos_thread_current());
   if (strcmp(thread_name, "FILESYS") != 0 && strcmp(thread_name, "HFilesys") != 0)
   {
      fprintf(stderr,"%s: vc_hostfs is deprecated. Please use stdio\n",
              vcos_thread_get_name(vcos_thread_current()));
   }

   vcos_log_register("hostfs", &hostfs_log_cat);
   DEBUG_MINOR("init");
   // Allocate memory for the file info table
   p_file_info_table = (file_info_t *)calloc( FILE_INFO_TABLE_CHUNK_LEN, sizeof( file_info_t ) );
   assert( p_file_info_table != NULL );
   if (p_file_info_table)
   {
      file_info_table_len = FILE_INFO_TABLE_CHUNK_LEN;
   }
}