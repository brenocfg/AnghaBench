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
struct d_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 int d_next_char (struct d_info*) ; 
 int /*<<< orphan*/  d_number (struct d_info*) ; 

__attribute__((used)) static int
d_call_offset (struct d_info *di, int c)
{
  if (c == '\0')
    c = d_next_char (di);

  if (c == 'h')
    d_number (di);
  else if (c == 'v')
    {
      d_number (di);
      if (! d_check_char (di, '_'))
	return 0;
      d_number (di);
    }
  else
    return 0;

  if (! d_check_char (di, '_'))
    return 0;

  return 1;
}