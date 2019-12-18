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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* alloca (size_t) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 size_t graph_dump_format ; 
 char const** graph_ext ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 size_t vcg ; 

void
finish_graph_dump_file (const char *base)
{
  size_t namelen = strlen (base);
  size_t extlen = strlen (graph_ext[graph_dump_format]) + 1;
  char *buf = alloca (namelen + extlen);
  FILE *fp;

  memcpy (buf, base, namelen);
  memcpy (buf + namelen, graph_ext[graph_dump_format], extlen);

  fp = fopen (buf, "a");
  if (fp != NULL)
    {
      gcc_assert (graph_dump_format == vcg);
      fputs ("}\n", fp);
      fclose (fp);
    }
}