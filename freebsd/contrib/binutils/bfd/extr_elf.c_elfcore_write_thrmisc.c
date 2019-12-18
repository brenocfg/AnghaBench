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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  NT_THRMISC ; 
 char* elfcore_write_note (int /*<<< orphan*/ *,char*,int*,char*,int /*<<< orphan*/ ,char const*,int) ; 

char *
elfcore_write_thrmisc (bfd *abfd,
		       char *buf,
		       int *bufsiz,
		       const char *tname,
		       int size)
{
#if defined (HAVE_THRMISC_T)
  char *note_name = "CORE";
  return elfcore_write_note (abfd, buf, bufsiz,
			     note_name, NT_THRMISC, tname, size);
#else
  return buf;
#endif
}