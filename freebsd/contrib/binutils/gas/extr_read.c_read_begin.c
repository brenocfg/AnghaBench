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

/* Variables and functions */
 int /*<<< orphan*/  chunksize ; 
 int /*<<< orphan*/  cond_obstack ; 
 scalar_t__ flag_mri ; 
 int* is_end_of_line ; 
 int* lex_type ; 
 char* line_separator_chars ; 
 int /*<<< orphan*/  notes ; 
 int /*<<< orphan*/  obj_read_begin_hook () ; 
 int /*<<< orphan*/  obstack_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pobegin () ; 

void
read_begin (void)
{
  const char *p;

  pobegin ();
  obj_read_begin_hook ();

  /* Something close -- but not too close -- to a multiple of 1024.
     The debugging malloc I'm using has 24 bytes of overhead.  */
  obstack_begin (&notes, chunksize);
  obstack_begin (&cond_obstack, chunksize);

  /* Use machine dependent syntax.  */
  for (p = line_separator_chars; *p; p++)
    is_end_of_line[(unsigned char) *p] = 1;
  /* Use more.  FIXME-SOMEDAY.  */

  if (flag_mri)
    lex_type['?'] = 3;
}