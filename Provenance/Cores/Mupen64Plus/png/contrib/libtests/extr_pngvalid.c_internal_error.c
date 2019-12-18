#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct exception_context {int dummy; } ;
struct TYPE_4__ {struct exception_context exception_context; } ;
typedef  TYPE_1__ png_store ;
typedef  int /*<<< orphan*/  png_const_charp ;
typedef  int /*<<< orphan*/  Throw ;

/* Variables and functions */
 int /*<<< orphan*/  store_log (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
internal_error(png_store *ps, png_const_charp message)
{
   store_log(ps, NULL, message, 1 /* error */);

   /* And finally throw an exception. */
   {
      struct exception_context *the_exception_context = &ps->exception_context;
      Throw ps;
   }
}