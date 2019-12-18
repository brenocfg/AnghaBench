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
struct file_archive_file_backend {int dummy; } ;

/* Variables and functions */
 struct file_archive_file_backend const sevenzip_backend ; 

const struct file_archive_file_backend *file_archive_get_7z_file_backend(void)
{
#ifdef HAVE_7ZIP
   return &sevenzip_backend;
#else
   return NULL;
#endif
}