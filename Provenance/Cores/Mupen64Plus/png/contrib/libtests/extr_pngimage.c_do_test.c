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
struct display {int /*<<< orphan*/  error_return; } ;

/* Variables and functions */
 int ERRORS ; 
 int /*<<< orphan*/  INTERNAL_ERROR ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*,int) ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_one_file (struct display*,char const*) ; 

__attribute__((used)) static int
do_test(struct display *dp, const char *file)
   /* Exists solely to isolate the setjmp clobbers */
{
   int ret = setjmp(dp->error_return);

   if (ret == 0)
   {
      test_one_file(dp, file);
      return 0;
   }

   else if (ret < ERRORS) /* shouldn't longjmp on warnings */
      display_log(dp, INTERNAL_ERROR, "unexpected return code %d", ret);

   return ret;
}