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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 int /*<<< orphan*/  expect (char*,int) ; 
 int /*<<< orphan*/  printf_stdebug (char*) ; 

__attribute__((used)) static void
st2000_resume (ptid_t ptid, int step, enum target_signal sig)
{
  if (step)
    {
      printf_stdebug ("ST\r");
      /* Wait for the echo.  */
      expect ("ST\r", 1);
    }
  else
    {
      printf_stdebug ("GO\r");
      /* Swallow the echo.  */
      expect ("GO\r", 1);
    }
}