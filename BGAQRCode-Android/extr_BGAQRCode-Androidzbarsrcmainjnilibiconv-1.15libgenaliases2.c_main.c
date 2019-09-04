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
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main (int argc, char* argv[])
{
  const char* tag;
  char* aliases_file_name;
  char* canonical_file_name;
  FILE* aliases_file;
  FILE* canonical_file;

  if (argc != 4) {
    fprintf(stderr, "Usage: genaliases2 tag aliases.h canonical.h\n");
    exit(1);
  }

  tag = argv[1];
  aliases_file_name = argv[2];
  canonical_file_name = argv[3];

  aliases_file = fopen(aliases_file_name, "w");
  if (aliases_file == NULL) {
    fprintf(stderr, "Could not open '%s' for writing\n", aliases_file_name);
    exit(1);
  }

  canonical_file = fopen(canonical_file_name, "w");
  if (canonical_file == NULL) {
    fprintf(stderr, "Could not open '%s' for writing\n", canonical_file_name);
    exit(1);
  }

#define DEFENCODING(xxx_names,xxx,xxx_ifuncs1,xxx_ifuncs2,xxx_ofuncs1,xxx_ofuncs2) \
  {                                                           \
    static const char* const names[] = BRACIFY xxx_names;     \
    emit_encoding(aliases_file,canonical_file,tag,names,sizeof(names)/sizeof(names[0]),#xxx); \
  }
#define BRACIFY(...) { __VA_ARGS__ }
#define DEFALIAS(xxx_alias,xxx) emit_alias(aliases_file,tag,xxx_alias,#xxx);
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
  if (ferror(aliases_file) || fclose(aliases_file))
    exit(1);
  if (ferror(canonical_file) || fclose(canonical_file))
    exit(1);
  exit(0);
}