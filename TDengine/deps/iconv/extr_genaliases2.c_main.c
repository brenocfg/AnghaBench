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
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdout ; 

int main (int argc, char* argv[])
{
  const char * tag = (argc > 1 ? argv[1] : "xxx");
  FILE * stdout2 = fdopen(3, "w");
  if (stdout2 == NULL)
    exit(1);
#define DEFENCODING(xxx_names,xxx,xxx_ifuncs1,xxx_ifuncs2,xxx_ofuncs1,xxx_ofuncs2) \
  {                                                           \
    static const char* const names[] = BRACIFY xxx_names;     \
    emit_encoding(stdout,stdout2,tag,names,sizeof(names)/sizeof(names[0]),#xxx); \
  }
#define BRACIFY(...) { __VA_ARGS__ }
#define DEFALIAS(xxx_alias,xxx) emit_alias(stdout,tag,xxx_alias,#xxx);
#ifdef USE_AIX
#include "encodings_aix.def"
#endif
#ifdef USE_OSF1
#include "encodings_osf1.def"
#endif
#ifdef USE_DOS
#include "encodings_dos.def"
#endif
#ifdef USE_EXTRA
#include "encodings_extra.def"
#endif
#undef DEFALIAS
#undef BRACIFY
#undef DEFENCODING
  if (ferror(stdout) || fclose(stdout) || ferror(stdout2) || fclose(stdout2))
    exit(1);
  exit(0);
}