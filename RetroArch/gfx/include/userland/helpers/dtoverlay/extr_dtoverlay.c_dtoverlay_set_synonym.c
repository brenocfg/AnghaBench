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
typedef  int /*<<< orphan*/  DTBLOB_T ;

/* Variables and functions */
 int dtoverlay_dup_property (int /*<<< orphan*/ *,char*,char const*,char const*) ; 

int dtoverlay_set_synonym(DTBLOB_T *dtb, const char *dst, const char *src)
{
   /* Add/update all aliases, symbols and overrides named dst
      to be equivalent to those named src.
      An absent src is ignored.
   */
   int err;

   err = dtoverlay_dup_property(dtb, "/aliases", dst, src);
   if (err == 0)
      err = dtoverlay_dup_property(dtb, "/__symbols__", dst, src);
   if (err == 0)
      dtoverlay_dup_property(dtb, "/__overrides__", dst, src);
   return err;
}