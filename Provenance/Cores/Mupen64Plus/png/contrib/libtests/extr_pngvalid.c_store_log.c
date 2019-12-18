#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nerrors; scalar_t__ verbose; int /*<<< orphan*/  error; int /*<<< orphan*/  nwarnings; } ;
typedef  TYPE_1__ png_store ;
typedef  int /*<<< orphan*/  png_const_structp ;
typedef  int /*<<< orphan*/  png_const_charp ;

/* Variables and functions */
 int /*<<< orphan*/  store_message (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_verbose (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
store_log(png_store* ps, png_const_structp pp, png_const_charp message,
   int is_error)
{
   /* The warning is copied to the error buffer if there are no errors and it is
    * the first warning.  The error is copied to the error buffer if it is the
    * first error (overwriting any prior warnings).
    */
   if (is_error ? (ps->nerrors)++ == 0 :
       (ps->nwarnings)++ == 0 && ps->nerrors == 0)
      store_message(ps, pp, ps->error, sizeof ps->error, 0, message);

   if (ps->verbose)
      store_verbose(ps, pp, is_error ? "error: " : "warning: ", message);
}