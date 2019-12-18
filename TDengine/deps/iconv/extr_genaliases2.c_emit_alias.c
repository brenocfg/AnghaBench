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
 int counter ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  putc (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emit_alias (FILE* out1, const char* tag, const char* alias, const char* c_name)
{
  fprintf(out1,"  S(%s_%u, \"",tag,counter);
  /* Output alias in upper case. */
  {
    const char* s = alias;
    for (; *s; s++) {
      unsigned char c = * (unsigned char *) s;
      if (c >= 0x80)
        exit(1);
      if (c >= 'a' && c <= 'z')
        c -= 'a'-'A';
      putc(c, out1);
    }
  }
  fprintf(out1,"\", ei_%s )\n", c_name);
  counter++;
}