#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
typedef  int png_size_t ;
typedef  TYPE_2__* png_inforp ;
struct TYPE_8__ {int /*<<< orphan*/ * signature; } ;
struct TYPE_7__ {int sig_bytes; int io_state; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_HAVE_PNG_SIGNATURE ; 
 int PNG_IO_READING ; 
 int PNG_IO_SIGNATURE ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_read_data (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ png_sig_cmp (int /*<<< orphan*/ *,int,int) ; 

void /* PRIVATE */
png_read_sig(png_structrp png_ptr, png_inforp info_ptr)
{
   png_size_t num_checked, num_to_check;

   /* Exit if the user application does not expect a signature. */
   if (png_ptr->sig_bytes >= 8)
      return;

   num_checked = png_ptr->sig_bytes;
   num_to_check = 8 - num_checked;

#ifdef PNG_IO_STATE_SUPPORTED
   png_ptr->io_state = PNG_IO_READING | PNG_IO_SIGNATURE;
#endif

   /* The signature must be serialized in a single I/O call. */
   png_read_data(png_ptr, &(info_ptr->signature[num_checked]), num_to_check);
   png_ptr->sig_bytes = 8;

   if (png_sig_cmp(info_ptr->signature, num_checked, num_to_check) != 0)
   {
      if (num_checked < 4 &&
          png_sig_cmp(info_ptr->signature, num_checked, num_to_check - 4))
         png_error(png_ptr, "Not a PNG file");
      else
         png_error(png_ptr, "PNG file corrupted by ASCII conversion");
   }
   if (num_checked < 3)
      png_ptr->mode |= PNG_HAVE_PNG_SIGNATURE;
}