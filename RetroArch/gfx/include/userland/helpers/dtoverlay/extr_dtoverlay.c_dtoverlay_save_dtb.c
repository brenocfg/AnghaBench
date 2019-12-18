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
struct TYPE_3__ {long trailer_len; int /*<<< orphan*/  trailer; int /*<<< orphan*/  fdt; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ DTBLOB_T ;

/* Variables and functions */
 int /*<<< orphan*/  dtoverlay_debug (char*,...) ; 
 int /*<<< orphan*/  dtoverlay_error (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 long fdt_totalsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 long fwrite (int /*<<< orphan*/ ,int,long,int /*<<< orphan*/ *) ; 

int dtoverlay_save_dtb(const DTBLOB_T *dtb, const char *filename)
{
   FILE *fp = fopen(filename, "wb");
   int err = 0;

   if (fp)
   {
      long len = fdt_totalsize(dtb->fdt);
      if (len != fwrite(dtb->fdt, 1, len, fp))
      {
         dtoverlay_error("fwrite failed");
         err = -2;
         goto error_exit;
      }
      if (dtb->trailer_len &&
          (fwrite(dtb->trailer, 1, dtb->trailer_len, fp) != dtb->trailer_len))
      {
         dtoverlay_error("fwrite failed");
         err = -2;
         goto error_exit;
      }

      dtoverlay_debug("Wrote %ld bytes to '%s'", len, filename);
      fclose(fp);
   }
   else
   {
      dtoverlay_debug("Failed to create '%s'", filename);
      err = -1;
   }

error_exit:
   return err;
}