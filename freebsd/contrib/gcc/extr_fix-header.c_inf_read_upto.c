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
struct TYPE_5__ {scalar_t__* ptr; } ;
typedef  TYPE_1__ sstring ;

/* Variables and functions */
 int EOF ; 
 int INF_GET () ; 
 int /*<<< orphan*/  MAKE_SSTRING_SPACE (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SSTRING_PUT (TYPE_1__*,int) ; 

__attribute__((used)) static int
inf_read_upto (sstring *str, int delim)
{
  int ch;
  for (;;)
    {
      ch = INF_GET ();
      if (ch == EOF || ch == delim)
	break;
      SSTRING_PUT (str, ch);
    }
  MAKE_SSTRING_SPACE (str, 1);
  *str->ptr = 0;
  return ch;
}