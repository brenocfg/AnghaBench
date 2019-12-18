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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  ISPRINT (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,char*) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 int /*<<< orphan*/  bfd_error_file_truncated ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,char*) ; 

__attribute__((used)) static void
ihex_bad_byte (bfd *abfd, unsigned int lineno, int c, bfd_boolean error)
{
  if (c == EOF)
    {
      if (! error)
	bfd_set_error (bfd_error_file_truncated);
    }
  else
    {
      char buf[10];

      if (! ISPRINT (c))
	sprintf (buf, "\\%03o", (unsigned int) c);
      else
	{
	  buf[0] = c;
	  buf[1] = '\0';
	}
      (*_bfd_error_handler)
	(_("%B:%d: unexpected character `%s' in Intel Hex file"),
	 abfd, lineno, buf);
      bfd_set_error (bfd_error_bad_value);
    }
}