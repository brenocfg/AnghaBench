#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct section_offsets {int* offsets; } ;
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_sections; int /*<<< orphan*/  section_offsets; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 size_t SECT_OFF_BSS (TYPE_1__*) ; 
 size_t SECT_OFF_DATA (TYPE_1__*) ; 
 size_t SECT_OFF_TEXT (TYPE_1__*) ; 
 int /*<<< orphan*/  SIZEOF_N_SECTION_OFFSETS (int /*<<< orphan*/ ) ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int fromhex (int /*<<< orphan*/ ) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct section_offsets*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objfile_relocate (TYPE_1__*,struct section_offsets*) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 TYPE_1__* symfile_objfile ; 
 int /*<<< orphan*/  warning (char*,char*) ; 

__attribute__((used)) static void
get_offsets (void)
{
  struct remote_state *rs = get_remote_state ();
  char *buf = alloca (rs->remote_packet_size);
  char *ptr;
  int lose;
  CORE_ADDR text_addr, data_addr, bss_addr;
  struct section_offsets *offs;

  putpkt ("qOffsets");

  getpkt (buf, (rs->remote_packet_size), 0);

  if (buf[0] == '\000')
    return;			/* Return silently.  Stub doesn't support
				   this command. */
  if (buf[0] == 'E')
    {
      warning ("Remote failure reply: %s", buf);
      return;
    }

  /* Pick up each field in turn.  This used to be done with scanf, but
     scanf will make trouble if CORE_ADDR size doesn't match
     conversion directives correctly.  The following code will work
     with any size of CORE_ADDR.  */
  text_addr = data_addr = bss_addr = 0;
  ptr = buf;
  lose = 0;

  if (strncmp (ptr, "Text=", 5) == 0)
    {
      ptr += 5;
      /* Don't use strtol, could lose on big values.  */
      while (*ptr && *ptr != ';')
	text_addr = (text_addr << 4) + fromhex (*ptr++);
    }
  else
    lose = 1;

  if (!lose && strncmp (ptr, ";Data=", 6) == 0)
    {
      ptr += 6;
      while (*ptr && *ptr != ';')
	data_addr = (data_addr << 4) + fromhex (*ptr++);
    }
  else
    lose = 1;

  if (!lose && strncmp (ptr, ";Bss=", 5) == 0)
    {
      ptr += 5;
      while (*ptr && *ptr != ';')
	bss_addr = (bss_addr << 4) + fromhex (*ptr++);
    }
  else
    lose = 1;

  if (lose)
    error ("Malformed response to offset query, %s", buf);

  if (symfile_objfile == NULL)
    return;

  offs = ((struct section_offsets *)
	  alloca (SIZEOF_N_SECTION_OFFSETS (symfile_objfile->num_sections)));
  memcpy (offs, symfile_objfile->section_offsets,
	  SIZEOF_N_SECTION_OFFSETS (symfile_objfile->num_sections));

  offs->offsets[SECT_OFF_TEXT (symfile_objfile)] = text_addr;

  /* This is a temporary kludge to force data and bss to use the same offsets
     because that's what nlmconv does now.  The real solution requires changes
     to the stub and remote.c that I don't have time to do right now.  */

  offs->offsets[SECT_OFF_DATA (symfile_objfile)] = data_addr;
  offs->offsets[SECT_OFF_BSS (symfile_objfile)] = data_addr;

  objfile_relocate (symfile_objfile, offs);
}