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
typedef  int /*<<< orphan*/  png_uint_32 ;
struct TYPE_4__ {char const* test; int /*<<< orphan*/  error_return; } ;
typedef  TYPE_1__ display ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char const* init ; 
 int /*<<< orphan*/  perform_one_test (int /*<<< orphan*/ *,int,char const**,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
perform_one_test_safe(FILE *fp, int argc, const char **argv,
   png_uint_32 *default_flags, display *d, const char *test)
{
   if (setjmp(d->error_return) == 0)
   {
      d->test = test; /* allow use of d->error_return */
#     ifdef PNG_SAVE_UNKNOWN_CHUNKS_SUPPORTED
         perform_one_test(fp, argc, argv, default_flags, d, 0);
#     endif
#     ifdef PNG_READ_USER_CHUNKS_SUPPORTED
         perform_one_test(fp, argc, argv, default_flags, d, 1);
#     endif
      d->test = init; /* prevent use of d->error_return */
   }
}