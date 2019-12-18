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
struct display {scalar_t__ results; int /*<<< orphan*/  original_ip; int /*<<< orphan*/  original_pp; scalar_t__ chunks; int /*<<< orphan*/ * original_rows; scalar_t__ original_rowbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  display_clean_read (struct display*) ; 
 int /*<<< orphan*/  display_clean_write (struct display*) ; 
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
display_clean(struct display *dp)
{
#  ifdef PNG_WRITE_PNG_SUPPORTED
      display_clean_write(dp);
#  endif
   display_clean_read(dp);

   dp->original_rowbytes = 0;
   dp->original_rows = NULL;
   dp->chunks = 0;

   png_destroy_read_struct(&dp->original_pp, &dp->original_ip, NULL);
   /* leave the filename for error detection */
   dp->results = 0; /* reset for next time */
}