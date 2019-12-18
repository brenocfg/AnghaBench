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
struct bit_field {int length; unsigned long start; int /*<<< orphan*/ * suffix; int /*<<< orphan*/ * prefix; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  monitor_expect (int /*<<< orphan*/ *,char*,int) ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned long
fetch_fields (struct bit_field *bf)
{
  char buf[20];
  unsigned long val = 0;
  unsigned long bits;

  for (; bf->prefix != NULL; bf++)
    {
      monitor_expect (bf->prefix, NULL, 0);	/* get prefix */
      monitor_expect (bf->suffix, buf, sizeof (buf));	/* hex value, suffix */
      if (bf->length != 0)
	{
	  bits = strtoul (buf, NULL, 16);	/* get field value */
	  bits &= ((1 << bf->length) - 1);	/* mask out useless bits */
	  val |= bits << bf->start;	/* insert into register */
	}

    }

  return val;
}