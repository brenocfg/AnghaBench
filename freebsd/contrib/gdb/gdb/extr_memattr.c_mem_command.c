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
struct mem_attrib {int hwbreak; int cache; int verify; int /*<<< orphan*/  width; int /*<<< orphan*/  mode; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_RO ; 
 int /*<<< orphan*/  MEM_RW ; 
 int /*<<< orphan*/  MEM_WIDTH_16 ; 
 int /*<<< orphan*/  MEM_WIDTH_32 ; 
 int /*<<< orphan*/  MEM_WIDTH_64 ; 
 int /*<<< orphan*/  MEM_WIDTH_8 ; 
 int /*<<< orphan*/  MEM_WO ; 
 int /*<<< orphan*/  create_mem_region (int,int,struct mem_attrib*) ; 
 struct mem_attrib default_mem_attrib ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int parse_and_eval_address (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void
mem_command (char *args, int from_tty)
{
  CORE_ADDR lo, hi;
  char *tok;
  struct mem_attrib attrib;

  if (!args)
    error_no_arg ("No mem");

  tok = strtok (args, " \t");
  if (!tok)
    error ("no lo address");
  lo = parse_and_eval_address (tok);

  tok = strtok (NULL, " \t");
  if (!tok)
    error ("no hi address");
  hi = parse_and_eval_address (tok);

  attrib = default_mem_attrib;
  while ((tok = strtok (NULL, " \t")) != NULL)
    {
      if (strcmp (tok, "rw") == 0)
	attrib.mode = MEM_RW;
      else if (strcmp (tok, "ro") == 0)
	attrib.mode = MEM_RO;
      else if (strcmp (tok, "wo") == 0)
	attrib.mode = MEM_WO;

      else if (strcmp (tok, "8") == 0)
	attrib.width = MEM_WIDTH_8;
      else if (strcmp (tok, "16") == 0)
	{
	  if ((lo % 2 != 0) || (hi % 2 != 0))
	    error ("region bounds not 16 bit aligned");
	  attrib.width = MEM_WIDTH_16;
	}
      else if (strcmp (tok, "32") == 0)
	{
	  if ((lo % 4 != 0) || (hi % 4 != 0))
	    error ("region bounds not 32 bit aligned");
	  attrib.width = MEM_WIDTH_32;
	}
      else if (strcmp (tok, "64") == 0)
	{
	  if ((lo % 8 != 0) || (hi % 8 != 0))
	    error ("region bounds not 64 bit aligned");
	  attrib.width = MEM_WIDTH_64;
	}

#if 0
      else if (strcmp (tok, "hwbreak") == 0)
	attrib.hwbreak = 1;
      else if (strcmp (tok, "swbreak") == 0)
	attrib.hwbreak = 0;
#endif

      else if (strcmp (tok, "cache") == 0)
	attrib.cache = 1;
      else if (strcmp (tok, "nocache") == 0)
	attrib.cache = 0;

#if 0
      else if (strcmp (tok, "verify") == 0)
	attrib.verify = 1;
      else if (strcmp (tok, "noverify") == 0)
	attrib.verify = 0;
#endif

      else
	error ("unknown attribute: %s", tok);
    }

  create_mem_region (lo, hi, &attrib);
}