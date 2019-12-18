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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int HAS_SYMS ; 
 scalar_t__ bfd_canonicalize_symtab (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int bfd_get_file_flags (int /*<<< orphan*/ *) ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_symtab_upper_bound (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 scalar_t__ remove_useless_symbols (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * symbols ; 
 scalar_t__ symcount ; 
 scalar_t__ symstorage ; 

__attribute__((used)) static void slurp_symtab(const char *filename)
{
  bfd *abfd;

  symcount = 0;

  abfd = bfd_openr(filename, NULL);
  if (abfd == NULL) {
    fprintf(stderr, "failed to open: %s\n", filename);
    goto no_symbols;
  }

  if (!bfd_check_format(abfd, bfd_object))
    goto no_symbols;

  if (!(bfd_get_file_flags(abfd) & HAS_SYMS))
    goto no_symbols;

  symstorage = bfd_get_symtab_upper_bound(abfd);
  if (symstorage <= 0)
    goto no_symbols;

  symbols = malloc(symstorage);
  if (symbols == NULL)
    goto no_symbols;

  symcount = bfd_canonicalize_symtab(abfd, symbols);
  if (symcount < 0)
    goto no_symbols;

  symcount = remove_useless_symbols(symbols, symcount);
//  bfd_close(abfd);
  return;

no_symbols:
  fprintf(stderr, "no symbols in %s\n", bfd_get_filename(abfd));
  if (symbols != NULL)
    free(symbols);
  symbols = NULL;
  if (abfd != NULL)
    bfd_close(abfd);
}