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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  O_BINARY ; 
 int /*<<< orphan*/  STDIN ; 
 int /*<<< orphan*/  STDOUT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ pnm2png (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
  FILE *fp_rd = stdin;
  FILE *fp_al = NULL;
  FILE *fp_wr = stdout;
  BOOL interlace = FALSE;
  BOOL alpha = FALSE;
  int argi;

  for (argi = 1; argi < argc; argi++)
  {
    if (argv[argi][0] == '-')
    {
      switch (argv[argi][1])
      {
        case 'i':
          interlace = TRUE;
          break;
        case 'a':
          alpha = TRUE;
          argi++;
          if ((fp_al = fopen (argv[argi], "rb")) == NULL)
          {
            fprintf (stderr, "PNM2PNG\n");
            fprintf (stderr, "Error:  alpha-channel file %s does not exist\n",
               argv[argi]);
            exit (1);
          }
          break;
        case 'h':
        case '?':
          usage();
          exit(0);
          break;
        default:
          fprintf (stderr, "PNM2PNG\n");
          fprintf (stderr, "Error:  unknown option %s\n", argv[argi]);
          usage();
          exit(1);
          break;
      } /* end switch */
    }
    else if (fp_rd == stdin)
    {
      if ((fp_rd = fopen (argv[argi], "rb")) == NULL)
      {
        fprintf (stderr, "PNM2PNG\n");
        fprintf (stderr, "Error:  file %s does not exist\n", argv[argi]);
        exit (1);
      }
    }
    else if (fp_wr == stdout)
    {
      if ((fp_wr = fopen (argv[argi], "wb")) == NULL)
      {
        fprintf (stderr, "PNM2PNG\n");
        fprintf (stderr, "Error:  can not create PNG-file %s\n", argv[argi]);
        exit (1);
      }
    }
    else
    {
      fprintf (stderr, "PNM2PNG\n");
      fprintf (stderr, "Error:  too many parameters\n");
      usage();
      exit (1);
    }
  } /* end for */

#ifdef __TURBOC__
  /* set stdin/stdout to binary, we're reading the PNM always! in binary format */
  if (fp_rd == stdin)
  {
    setmode (STDIN, O_BINARY);
  }
  if (fp_wr == stdout)
  {
    setmode (STDOUT, O_BINARY);
  }
#endif

  /* call the conversion program itself */
  if (pnm2png (fp_rd, fp_wr, fp_al, interlace, alpha) == FALSE)
  {
    fprintf (stderr, "PNM2PNG\n");
    fprintf (stderr, "Error:  unsuccessful converting to PNG-image\n");
    exit (1);
  }

  /* close input file */
  fclose (fp_rd);
  /* close output file */
  fclose (fp_wr);
  /* close alpha file */
  if (alpha)
    fclose (fp_al);

  return 0;
}