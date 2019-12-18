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
struct TYPE_2__ {char* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 TYPE_1__** string_table ; 
 int strlen (char*) ; 
 int strtablen ; 

__attribute__((used)) static void
print_string_table (void)
{
  int x;
  char lbuf[80], buf[80];
  int blen = 0;

  printf ("static const char * const ia64_strings[] = {\n");
  lbuf[0] = '\0';

  for (x = 0; x < strtablen; x++)
    {
      int len;
      
      if (strlen (string_table[x]->s) > 75)
	abort ();

      sprintf (buf, " \"%s\",", string_table[x]->s);
      len = strlen (buf);

      if ((blen + len) > 75)
	{
	  printf (" %s\n", lbuf);
	  lbuf[0] = '\0';
	  blen = 0;
	}
      strcat (lbuf, buf);
      blen += len;
    }

  if (blen > 0)
    printf (" %s\n", lbuf);

  printf ("};\n\n");
}