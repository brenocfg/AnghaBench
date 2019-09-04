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
typedef  scalar_t__ GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void glewPrintExt (const char* name, GLboolean def1, GLboolean def2, GLboolean def3)
{
  unsigned int i;
  fprintf(f, "\n%s:", name);
  for (i=0; i<62-strlen(name); i++) fprintf(f, " ");
  fprintf(f, "%s ", def1 ? "OK" : "MISSING");
  if (def1 != def2)
    fprintf(f, "[%s] ", def2 ? "OK" : "MISSING");
  if (def1 != def3)
    fprintf(f, "[%s]\n", def3 ? "OK" : "MISSING");
  else
    fprintf(f, "\n");
  for (i=0; i<strlen(name)+1; i++) fprintf(f, "-");
  fprintf(f, "\n");
  fflush(f);
}