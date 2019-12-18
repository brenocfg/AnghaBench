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
struct MY_STAT {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  IntNative ;
typedef  size_t Int32 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Char ;
typedef  void* Bool ;

/* Variables and functions */
 size_t BZ_N_SUFFIX_PAIRS ; 
 int /*<<< orphan*/  ERROR_IF_NOT_ZERO (int /*<<< orphan*/ ) ; 
 void* False ; 
 int /*<<< orphan*/  MY_STAT (char*,struct MY_STAT*) ; 
 scalar_t__ MY_S_ISDIR (int /*<<< orphan*/ ) ; 
#define  SM_F2F 130 
#define  SM_F2O 129 
#define  SM_I2O 128 
 void* True ; 
 int /*<<< orphan*/  applySavedTimeInfoToOutputFile (char*) ; 
 scalar_t__ containsDubiousChars (char*) ; 
 int /*<<< orphan*/  copyFileName (char*,int /*<<< orphan*/ *) ; 
 size_t countHardLinks (char*) ; 
 void* deleteOutputOnInterrupt ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fileExists (char*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * fopen_output_safely (char*,char*) ; 
 scalar_t__ forceOverwrite ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* inName ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keepInputFiles ; 
 int /*<<< orphan*/  mapSuffix (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ noisy ; 
 scalar_t__ notAStandardFile (char*) ; 
 char* outName ; 
 int /*<<< orphan*/ * outputHandleJustInCase ; 
 int /*<<< orphan*/  pad (char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 char* progName ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  saveInputFileMetaInfo (char*) ; 
 int /*<<< orphan*/  setExit (int) ; 
 int srcMode ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 void* uncompressStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* unzFailsExist ; 
 int /*<<< orphan*/ * unzSuffix ; 
 int verbosity ; 
 int /*<<< orphan*/ * zSuffix ; 

__attribute__((used)) static 
void uncompress ( Char *name )
{
   FILE  *inStr;
   FILE  *outStr;
   Int32 n, i;
   Bool  magicNumberOK;
   Bool  cantGuess;
   struct MY_STAT statBuf;

   deleteOutputOnInterrupt = False;

   if (name == NULL && srcMode != SM_I2O)
      panic ( "uncompress: bad modes\n" );

   cantGuess = False;
   switch (srcMode) {
      case SM_I2O: 
         copyFileName ( inName, (Char*)"(stdin)" );
         copyFileName ( outName, (Char*)"(stdout)" ); 
         break;
      case SM_F2F: 
         copyFileName ( inName, name );
         copyFileName ( outName, name );
         for (i = 0; i < BZ_N_SUFFIX_PAIRS; i++)
            if (mapSuffix(outName,zSuffix[i],unzSuffix[i]))
               goto zzz; 
         cantGuess = True;
         strcat ( outName, ".out" );
         break;
      case SM_F2O: 
         copyFileName ( inName, name );
         copyFileName ( outName, (Char*)"(stdout)" ); 
         break;
   }

   zzz:
   if ( srcMode != SM_I2O && containsDubiousChars ( inName ) ) {
      if (noisy)
      fprintf ( stderr, "%s: There are no files matching `%s'.\n",
                progName, inName );
      setExit(1);
      return;
   }
   if ( srcMode != SM_I2O && !fileExists ( inName ) ) {
      fprintf ( stderr, "%s: Can't open input file %s: %s.\n",
                progName, inName, strerror(errno) );
      setExit(1);
      return;
   }
   if ( srcMode == SM_F2F || srcMode == SM_F2O ) {
      MY_STAT(inName, &statBuf);
      if ( MY_S_ISDIR(statBuf.st_mode) ) {
         fprintf( stderr,
                  "%s: Input file %s is a directory.\n",
                  progName,inName);
         setExit(1);
         return;
      }
   }
   if ( srcMode == SM_F2F && !forceOverwrite && notAStandardFile ( inName )) {
      if (noisy)
      fprintf ( stderr, "%s: Input file %s is not a normal file.\n",
                progName, inName );
      setExit(1);
      return;
   }
   if ( /* srcMode == SM_F2F implied && */ cantGuess ) {
      if (noisy)
      fprintf ( stderr, 
                "%s: Can't guess original name for %s -- using %s\n",
                progName, inName, outName );
      /* just a warning, no return */
   }   
   if ( srcMode == SM_F2F && fileExists ( outName ) ) {
      if (forceOverwrite) {
	remove(outName);
      } else {
        fprintf ( stderr, "%s: Output file %s already exists.\n",
                  progName, outName );
        setExit(1);
        return;
      }
   }
   if ( srcMode == SM_F2F && !forceOverwrite &&
        (n=countHardLinks ( inName ) ) > 0) {
      fprintf ( stderr, "%s: Input file %s has %d other link%s.\n",
                progName, inName, n, n > 1 ? "s" : "" );
      setExit(1);
      return;
   }

   if ( srcMode == SM_F2F ) {
      /* Save the file's meta-info before we open it.  Doing it later
         means we mess up the access times. */
      saveInputFileMetaInfo ( inName );
   }

   switch ( srcMode ) {

      case SM_I2O:
         inStr = stdin;
         outStr = stdout;
         if ( isatty ( fileno ( stdin ) ) ) {
            fprintf ( stderr,
                      "%s: I won't read compressed data from a terminal.\n",
                      progName );
            fprintf ( stderr, "%s: For help, type: `%s --help'.\n",
                              progName, progName );
            setExit(1);
            return;
         };
         break;

      case SM_F2O:
         inStr = fopen ( inName, "rb" );
         outStr = stdout;
         if ( inStr == NULL ) {
            fprintf ( stderr, "%s: Can't open input file %s:%s.\n",
                      progName, inName, strerror(errno) );
            if ( inStr != NULL ) fclose ( inStr );
            setExit(1);
            return;
         };
         break;

      case SM_F2F:
         inStr = fopen ( inName, "rb" );
         outStr = fopen_output_safely ( outName, "wb" );
         if ( outStr == NULL) {
            fprintf ( stderr, "%s: Can't create output file %s: %s.\n",
                      progName, outName, strerror(errno) );
            if ( inStr != NULL ) fclose ( inStr );
            setExit(1);
            return;
         }
         if ( inStr == NULL ) {
            fprintf ( stderr, "%s: Can't open input file %s: %s.\n",
                      progName, inName, strerror(errno) );
            if ( outStr != NULL ) fclose ( outStr );
            setExit(1);
            return;
         };
         break;

      default:
         panic ( "uncompress: bad srcMode" );
         break;
   }

   if (verbosity >= 1) {
      fprintf ( stderr, "  %s: ", inName );
      pad ( inName );
      fflush ( stderr );
   }

   /*--- Now the input and output handles are sane.  Do the Biz. ---*/
   outputHandleJustInCase = outStr;
   deleteOutputOnInterrupt = True;
   magicNumberOK = uncompressStream ( inStr, outStr );
   outputHandleJustInCase = NULL;

   /*--- If there was an I/O error, we won't get here. ---*/
   if ( magicNumberOK ) {
      if ( srcMode == SM_F2F ) {
         applySavedTimeInfoToOutputFile ( outName );
         deleteOutputOnInterrupt = False;
         if ( !keepInputFiles ) {
            IntNative retVal = remove ( inName );
            ERROR_IF_NOT_ZERO ( retVal );
         }
      }
   } else {
      unzFailsExist = True;
      deleteOutputOnInterrupt = False;
      if ( srcMode == SM_F2F ) {
         IntNative retVal = remove ( outName );
         ERROR_IF_NOT_ZERO ( retVal );
      }
   }
   deleteOutputOnInterrupt = False;

   if ( magicNumberOK ) {
      if (verbosity >= 1)
         fprintf ( stderr, "done\n" );
   } else {
      setExit(2);
      if (verbosity >= 1)
         fprintf ( stderr, "not a bzip2 file.\n" ); else
         fprintf ( stderr,
                   "%s: %s is not a bzip2 file.\n",
                   progName, inName );
   }

}