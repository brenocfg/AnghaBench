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
struct mem_attrib {int mode; int width; scalar_t__ verify; scalar_t__ cache; scalar_t__ hwbreak; } ;
struct mem_region {scalar_t__ hi; struct mem_attrib attrib; scalar_t__ lo; scalar_t__ enabled_p; int /*<<< orphan*/  number; struct mem_region* next; } ;

/* Variables and functions */
#define  MEM_RO 135 
#define  MEM_RW 134 
#define  MEM_WIDTH_16 133 
#define  MEM_WIDTH_32 132 
#define  MEM_WIDTH_64 131 
#define  MEM_WIDTH_8 130 
#define  MEM_WIDTH_UNSPECIFIED 129 
#define  MEM_WO 128 
 int TARGET_ADDR_BIT ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 char* local_hex_string_custom (unsigned long,char*) ; 
 struct mem_region* mem_region_chain ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 

__attribute__((used)) static void
mem_info_command (char *args, int from_tty)
{
  struct mem_region *m;
  struct mem_attrib *attrib;

  if (!mem_region_chain)
    {
      printf_unfiltered ("There are no memory regions defined.\n");
      return;
    }

  printf_filtered ("Num ");
  printf_filtered ("Enb ");
  printf_filtered ("Low Addr   ");
  if (TARGET_ADDR_BIT > 32)
    printf_filtered ("        ");
  printf_filtered ("High Addr  ");
  if (TARGET_ADDR_BIT > 32)
    printf_filtered ("        ");
  printf_filtered ("Attrs ");
  printf_filtered ("\n");

  for (m = mem_region_chain; m; m = m->next)
    {
      char *tmp;
      printf_filtered ("%-3d %-3c\t",
		       m->number,
		       m->enabled_p ? 'y' : 'n');
      if (TARGET_ADDR_BIT <= 32)
	tmp = local_hex_string_custom ((unsigned long) m->lo, "08l");
      else
	tmp = local_hex_string_custom ((unsigned long) m->lo, "016l");
      
      printf_filtered ("%s ", tmp);

      if (TARGET_ADDR_BIT <= 32)
	{
	if (m->hi == 0)
	  tmp = "0x100000000";
	else
	  tmp = local_hex_string_custom ((unsigned long) m->hi, "08l");
	}
      else
	{
	if (m->hi == 0)
	  tmp = "0x10000000000000000";
	else
	  tmp = local_hex_string_custom ((unsigned long) m->hi, "016l");
	}

      printf_filtered ("%s ", tmp);

      /* Print a token for each attribute.

       * FIXME: Should we output a comma after each token?  It may
       * make it easier for users to read, but we'd lose the ability
       * to cut-and-paste the list of attributes when defining a new
       * region.  Perhaps that is not important.
       *
       * FIXME: If more attributes are added to GDB, the output may
       * become cluttered and difficult for users to read.  At that
       * time, we may want to consider printing tokens only if they
       * are different from the default attribute.  */

      attrib = &m->attrib;
      switch (attrib->mode)
	{
	case MEM_RW:
	  printf_filtered ("rw ");
	  break;
	case MEM_RO:
	  printf_filtered ("ro ");
	  break;
	case MEM_WO:
	  printf_filtered ("wo ");
	  break;
	}

      switch (attrib->width)
	{
	case MEM_WIDTH_8:
	  printf_filtered ("8 ");
	  break;
	case MEM_WIDTH_16:
	  printf_filtered ("16 ");
	  break;
	case MEM_WIDTH_32:
	  printf_filtered ("32 ");
	  break;
	case MEM_WIDTH_64:
	  printf_filtered ("64 ");
	  break;
	case MEM_WIDTH_UNSPECIFIED:
	  break;
	}

#if 0
      if (attrib->hwbreak)
	printf_filtered ("hwbreak");
      else
	printf_filtered ("swbreak");
#endif

      if (attrib->cache)
	printf_filtered ("cache ");
      else
	printf_filtered ("nocache ");

#if 0
      if (attrib->verify)
	printf_filtered ("verify ");
      else
	printf_filtered ("noverify ");
#endif

      printf_filtered ("\n");

      gdb_flush (gdb_stdout);
    }
}