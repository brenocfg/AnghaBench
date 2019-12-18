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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,char const*) ; 
 int /*<<< orphan*/  _IOFBF ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ fopen_utf8 (char const*,char*) ; 
 scalar_t__ log_file_buf ; 
 int /*<<< orphan*/ * log_file_fp ; 
 int log_file_initialized ; 
 int /*<<< orphan*/  logging_mtx ; 
 int /*<<< orphan*/  mutexInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * stderr ; 

void retro_main_log_file_init(const char *path, bool append)
{
   if (log_file_initialized)
      return;

#ifdef HAVE_LIBNX
   mutexInit(&logging_mtx);
#endif

   log_file_fp          = stderr;
   if (path == NULL)
      return;

   log_file_fp          = (FILE*)fopen_utf8(path, append ? "ab" : "wb");

   if (!log_file_fp)
   {
      log_file_fp       = stderr;
      RARCH_ERR("Failed to open system event log file: %s\n", path);
      return;
   }

   log_file_initialized = true;

#if !defined(PS2) /* TODO: PS2 IMPROVEMENT */
   /* TODO: this is only useful for a few platforms, find which and add ifdef */
   log_file_buf = calloc(1, 0x4000);
   setvbuf(log_file_fp, (char*)log_file_buf, _IOFBF, 0x4000);
#endif
}