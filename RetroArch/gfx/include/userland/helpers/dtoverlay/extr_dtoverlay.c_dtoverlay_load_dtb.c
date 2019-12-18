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
typedef  int /*<<< orphan*/  DTBLOB_T ;

/* Variables and functions */
 int /*<<< orphan*/  dtoverlay_error (char*,char const*) ; 
 int /*<<< orphan*/ * dtoverlay_load_dtb_from_fp (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 

DTBLOB_T *dtoverlay_load_dtb(const char *filename, int max_size)
{
   FILE *fp = fopen(filename, "rb");
   if (fp)
      return dtoverlay_load_dtb_from_fp(fp, max_size);
   dtoverlay_error("Failed to open '%s'", filename);
   return NULL;
}