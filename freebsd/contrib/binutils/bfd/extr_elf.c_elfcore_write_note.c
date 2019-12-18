#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  type; int /*<<< orphan*/  descsz; int /*<<< orphan*/  namesz; } ;
typedef  TYPE_1__ Elf_External_Note ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 char* realloc (char*,int) ; 
 int strlen (char const*) ; 

char *
elfcore_write_note (bfd *abfd,
		    char *buf,
		    int *bufsiz,
		    const char *name,
		    int type,
		    const void *input,
		    int size)
{
  Elf_External_Note *xnp;
  size_t namesz;
  size_t newspace;
  char *dest;

  namesz = 0;
  if (name != NULL)
    namesz = strlen (name) + 1;

  newspace = 12 + ((namesz + 3) & -4) + ((size + 3) & -4);

  buf = realloc (buf, *bufsiz + newspace);
  dest = buf + *bufsiz;
  *bufsiz += newspace;
  xnp = (Elf_External_Note *) dest;
  H_PUT_32 (abfd, namesz, xnp->namesz);
  H_PUT_32 (abfd, size, xnp->descsz);
  H_PUT_32 (abfd, type, xnp->type);
  dest = xnp->name;
  if (name != NULL)
    {
      memcpy (dest, name, namesz);
      dest += namesz;
      while (namesz & 3)
	{
	  *dest++ = '\0';
	  ++namesz;
	}
    }
  memcpy (dest, input, size);
  dest += size;
  while (size & 3)
    {
      *dest++ = '\0';
      ++size;
    }
  return buf;
}