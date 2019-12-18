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
typedef  int /*<<< orphan*/  png_store ;
typedef  int /*<<< orphan*/ * png_const_structp ;

/* Variables and functions */
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  store_log (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static void
store_pool_error(png_store *ps, png_const_structp pp, const char *msg)
{
   if (pp != NULL)
      png_error(pp, msg);

   /* Else we have to do it ourselves.  png_error eventually calls store_log,
    * above.  store_log accepts a NULL png_structp - it just changes what gets
    * output by store_message.
    */
   store_log(ps, pp, msg, 1 /* error */);
}