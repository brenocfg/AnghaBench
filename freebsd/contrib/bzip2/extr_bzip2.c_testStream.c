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
typedef  int /*<<< orphan*/  UChar ;
typedef  size_t Int32 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ Bool ;
typedef  int /*<<< orphan*/  BZFILE ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_bzRead (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BZ2_bzReadClose (size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BZ2_bzReadGetUnused (size_t*,int /*<<< orphan*/ *,void**,size_t*) ; 
 int /*<<< orphan*/ * BZ2_bzReadOpen (size_t*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,size_t) ; 
#define  BZ_CONFIG_ERROR 133 
#define  BZ_DATA_ERROR 132 
#define  BZ_DATA_ERROR_MAGIC 131 
#define  BZ_IO_ERROR 130 
 int BZ_MAX_UNUSED ; 
#define  BZ_MEM_ERROR 129 
 size_t BZ_OK ; 
 size_t BZ_STREAM_END ; 
#define  BZ_UNEXPECTED_EOF 128 
 size_t EOF ; 
 scalar_t__ False ; 
 int /*<<< orphan*/  SET_BINARY_MODE (int /*<<< orphan*/ *) ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  configError () ; 
 size_t fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* inName ; 
 int /*<<< orphan*/  ioError () ; 
 scalar_t__ myfeof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noisy ; 
 int /*<<< orphan*/  outOfMemory () ; 
 int /*<<< orphan*/  panic (char*) ; 
 char* progName ; 
 scalar_t__ smallMode ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int verbosity ; 

__attribute__((used)) static 
Bool testStream ( FILE *zStream )
{
   BZFILE* bzf = NULL;
   Int32   bzerr, bzerr_dummy, ret, streamNo, i;
   UChar   obuf[5000];
   UChar   unused[BZ_MAX_UNUSED];
   Int32   nUnused;
   void*   unusedTmpV;
   UChar*  unusedTmp;

   nUnused = 0;
   streamNo = 0;

   SET_BINARY_MODE(zStream);
   if (ferror(zStream)) goto errhandler_io;

   while (True) {

      bzf = BZ2_bzReadOpen ( 
               &bzerr, zStream, verbosity, 
               (int)smallMode, unused, nUnused
            );
      if (bzf == NULL || bzerr != BZ_OK) goto errhandler;
      streamNo++;

      while (bzerr == BZ_OK) {
         BZ2_bzRead ( &bzerr, bzf, obuf, 5000 );
         if (bzerr == BZ_DATA_ERROR_MAGIC) goto errhandler;
      }
      if (bzerr != BZ_STREAM_END) goto errhandler;

      BZ2_bzReadGetUnused ( &bzerr, bzf, &unusedTmpV, &nUnused );
      if (bzerr != BZ_OK) panic ( "test:bzReadGetUnused" );

      unusedTmp = (UChar*)unusedTmpV;
      for (i = 0; i < nUnused; i++) unused[i] = unusedTmp[i];

      BZ2_bzReadClose ( &bzerr, bzf );
      if (bzerr != BZ_OK) panic ( "test:bzReadGetUnused" );
      if (nUnused == 0 && myfeof(zStream)) break;

   }

   if (ferror(zStream)) goto errhandler_io;
   ret = fclose ( zStream );
   if (ret == EOF) goto errhandler_io;

   if (verbosity >= 2) fprintf ( stderr, "\n    " );
   return True;

   errhandler:
   BZ2_bzReadClose ( &bzerr_dummy, bzf );
   if (verbosity == 0) 
      fprintf ( stderr, "%s: %s: ", progName, inName );
   switch (bzerr) {
      case BZ_CONFIG_ERROR:
         configError(); break;
      case BZ_IO_ERROR:
         errhandler_io:
         ioError(); break;
      case BZ_DATA_ERROR:
         fprintf ( stderr,
                   "data integrity (CRC) error in data\n" );
         return False;
      case BZ_MEM_ERROR:
         outOfMemory();
      case BZ_UNEXPECTED_EOF:
         fprintf ( stderr,
                   "file ends unexpectedly\n" );
         return False;
      case BZ_DATA_ERROR_MAGIC:
         if (zStream != stdin) fclose(zStream);
         if (streamNo == 1) {
          fprintf ( stderr, 
                    "bad magic number (file not created by bzip2)\n" );
            return False;
         } else {
            if (noisy)
            fprintf ( stderr, 
                      "trailing garbage after EOF ignored\n" );
            return True;       
         }
      default:
         panic ( "test:unexpected error" );
   }

   panic ( "test:end" );
   return True; /*notreached*/
}