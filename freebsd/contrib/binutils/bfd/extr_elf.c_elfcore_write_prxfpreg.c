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
 int /*<<< orphan*/  NT_PRXFPREG ; 
 char* elfcore_write_note (int /*<<< orphan*/ *,char*,int*,char*,int /*<<< orphan*/ ,void const*,int) ; 

char *
elfcore_write_prxfpreg (bfd *abfd,
			char *buf,
			int *bufsiz,
			const void *xfpregs,
			int size)
{
  char *note_name = "LINUX";
  return elfcore_write_note (abfd, buf, bufsiz,
			     note_name, NT_PRXFPREG, xfpregs, size);
}