#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_13__ {size_t ifd; int /*<<< orphan*/  asym; } ;
struct TYPE_12__ {scalar_t__ iauxBase; int /*<<< orphan*/  caux; } ;
struct TYPE_11__ {int ifdMax; int iauxMax; int iextMax; scalar_t__ cbExtOffset; } ;
struct TYPE_10__ {scalar_t__ isym; } ;
typedef  int /*<<< orphan*/  FDR ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TARGET_VERSION ; 
 TYPE_1__* aux_symbols ; 
 int /*<<< orphan*/ * aux_used ; 
 int /*<<< orphan*/  e_strings ; 
 TYPE_8__* e_symbols ; 
 scalar_t__ errors ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_4__* file_desc ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int optind ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_aux (TYPE_1__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_file_desc (TYPE_4__*,int) ; 
 int /*<<< orphan*/  print_symbol (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,size_t,TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_tfile () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 TYPE_2__ sym_hdr ; 
 int /*<<< orphan*/  tfile ; 
 scalar_t__ tfile_fd ; 
 int /*<<< orphan*/  type_to_string (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ verbose ; 
 scalar_t__ version ; 
 char* version_string ; 
 scalar_t__ want_aux ; 
 int /*<<< orphan*/  want_line ; 
 int /*<<< orphan*/  want_rfd ; 
 scalar_t__ want_scope ; 

int
main (int argc, char **argv)
{
  int i, opt;

  /*
   * Process arguments
   */
  while ((opt = getopt_long (argc, argv, "alrsvt", options, NULL)) != -1)
    switch (opt)
      {
      default:	errors++;	break;
      case 'a': want_aux++;	break;	/* print aux table */
      case 'l': want_line++;	break;	/* print line numbers */
      case 'r': want_rfd++;	break;	/* print relative fd's */
      case 's':	want_scope++;	break;	/* print scope info */
      case 'v': verbose++;	break;  /* print version # */
      case 'V': version++;	break;  /* print version # */
      case 't': tfile++;	break;	/* this is a tfile (without header),
					   and not a .o */
      }

  if (version)
    {
      printf ("mips-tdump (GCC) %s\n", version_string);
      fputs ("Copyright (C) 2006 Free Software Foundation, Inc.\n", stdout);
      fputs ("This is free software; see the source for copying conditions.  There is NO\n\
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n",
             stdout);
      exit (0);
    }

  if (optind != argc - 1)
    errors++;

  if (verbose || errors)
    {
      fprintf (stderr, "mips-tdump (GCC) %s", version_string);
#ifdef TARGET_VERSION
      TARGET_VERSION;
#endif
      fputc ('\n', stderr);
    }

  if (errors)
    {
      fprintf (stderr, "Calling Sequence:\n");
      fprintf (stderr, "\t%s [-alrst] <object-or-T-file>\n", argv[0]);
      fprintf (stderr, "\n");
      fprintf (stderr, "switches:\n");
      fprintf (stderr, "\t-a Print out auxiliary table.\n");
      fprintf (stderr, "\t-l Print out line numbers.\n");
      fprintf (stderr, "\t-r Print out relative file descriptors.\n");
      fprintf (stderr, "\t-s Print out the current scopes for an item.\n");
      fprintf (stderr, "\t-t Assume there is no global header (ie, a T-file).\n");
      fprintf (stderr, "\t-v Print program version.\n");
      return 1;
    }

  /*
   * Open and process the input file.
   */
  tfile_fd = open (argv[optind], O_RDONLY);
  if (tfile_fd < 0)
    {
      perror (argv[optind]);
      return 1;
    }

  read_tfile ();

  /*
   * Print any global aux words if any.
   */
  if (want_aux)
    {
      long last_aux_in_use;

      if (sym_hdr.ifdMax != 0 && file_desc[0].iauxBase != 0)
	{
	  printf ("\nGlobal auxiliary entries before first file:\n");
	  for (i = 0; i < file_desc[0].iauxBase; i++)
	    print_aux (aux_symbols[i], 0, aux_used[i]);
	}

      if (sym_hdr.ifdMax == 0)
	last_aux_in_use = 0;
      else
	last_aux_in_use
	  = (file_desc[sym_hdr.ifdMax-1].iauxBase
	     + file_desc[sym_hdr.ifdMax-1].caux - 1);

      if (last_aux_in_use < sym_hdr.iauxMax-1)
	{
	  printf ("\nGlobal auxiliary entries after last file:\n");
	  for (i = last_aux_in_use; i < sym_hdr.iauxMax; i++)
	    print_aux (aux_symbols[i], i - last_aux_in_use, aux_used[i]);
	}
    }

  /*
   * Print the information for each file.
   */
  for (i = 0; i < sym_hdr.ifdMax; i++)
    print_file_desc (&file_desc[i], i);

  /*
   * Print the external symbols.
   */
  want_scope = 0;		/* scope info is meaning for extern symbols */
  printf ("\nThere are %lu external symbols, starting at %lu\n",
	  (ulong) sym_hdr.iextMax,
	  (ulong) sym_hdr.cbExtOffset);

  for(i = 0; i < sym_hdr.iextMax; i++)
    print_symbol (&e_symbols[i].asym, i, e_strings,
		  aux_symbols + file_desc[e_symbols[i].ifd].iauxBase,
		  e_symbols[i].ifd,
		  &file_desc[e_symbols[i].ifd]);

  /*
   * Print unused aux symbols now.
   */

  if (want_aux)
    {
      int first_time = 1;

      for (i = 0; i < sym_hdr.iauxMax; i++)
	{
	  if (! aux_used[i])
	    {
	      if (first_time)
		{
		  printf ("\nThe following auxiliary table entries were unused:\n\n");
		  first_time = 0;
		}

	      printf ("    #%-5d %11ld  0x%08lx  %s\n",
		      i,
		      (long) aux_symbols[i].isym,
		      (long) aux_symbols[i].isym,
		      type_to_string (aux_symbols, i, (FDR *) 0));
	    }
	}
    }

  return 0;
}