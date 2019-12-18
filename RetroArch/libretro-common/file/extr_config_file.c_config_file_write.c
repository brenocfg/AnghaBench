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
typedef  int /*<<< orphan*/  config_file_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  _IOFBF ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  config_file_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  config_file_dump_orbis (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fopen_utf8 (char const*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  orbisClose (int) ; 
 int orbisOpen (char const*,int,int) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

bool config_file_write(config_file_t *conf, const char *path, bool sort)
{
   if (!string_is_empty(path))
   {
#ifdef ORBIS
      int fd     = orbisOpen(path,O_RDWR|O_CREAT,0644);
      if (fd < 0)
         return false;
      config_file_dump_orbis(conf,fd);
      orbisClose(fd);
#else
      void* buf  = NULL;
      FILE *file = (FILE*)fopen_utf8(path, "wb");
      if (!file)
         return false;

      /* TODO: this is only useful for a few platforms, find which and add ifdef */
#if !defined(PS2) && !defined(PSP)
      buf = calloc(1, 0x4000);
      setvbuf(file, (char*)buf, _IOFBF, 0x4000);
#endif

      config_file_dump(conf, file, sort);

      if (file != stdout)
         fclose(file);
      if (buf)
         free(buf);
#endif
   }
   else
      config_file_dump(conf, stdout, sort);

   return true;
}