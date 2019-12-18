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
struct callback_data {char* zDbFilename; char* separator; char* nullvalue; int showHeader; int echoOn; int statsOn; scalar_t__ db; int /*<<< orphan*/  mode; int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  int sqlite3_int64 ;

/* Variables and functions */
 char* Argv0 ; 
 int /*<<< orphan*/  MODE_Column ; 
 int /*<<< orphan*/  MODE_Csv ; 
 int /*<<< orphan*/  MODE_Html ; 
 int /*<<< orphan*/  MODE_Line ; 
 int /*<<< orphan*/  MODE_List ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SQLITE_CONFIG_HEAP ; 
 int /*<<< orphan*/  SQLITE_CONFIG_MMAP_SIZE ; 
 char* SQLITE_SOURCE_ID ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int bail_on_error ; 
 char* cmdline_option_value (int,char**,int) ; 
 int do_meta_command (char*,struct callback_data*) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* find_home_dir () ; 
 int /*<<< orphan*/  fprintf (void*,char*,...) ; 
 scalar_t__ fputs ; 
 int /*<<< orphan*/  free (char*) ; 
 int integerValue (char const*) ; 
 int /*<<< orphan*/  interrupt_handler ; 
 int isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_init (struct callback_data*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  open_db (struct callback_data*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int process_input (struct callback_data*,int /*<<< orphan*/ ) ; 
 int process_sqliterc (struct callback_data*,char const*) ; 
 int /*<<< orphan*/  read_history (char*) ; 
 int /*<<< orphan*/  set_table_name (struct callback_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shell_callback ; 
 int shell_exec (scalar_t__,char*,int /*<<< orphan*/ ,struct callback_data*,char**) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_close (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_config (int /*<<< orphan*/ ,...) ; 
 char* sqlite3_libversion () ; 
 int /*<<< orphan*/  sqlite3_multiplex_initialize (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char*) ; 
 char* sqlite3_sourceid () ; 
 int /*<<< orphan*/ * sqlite3_vfs_find (char*) ; 
 int /*<<< orphan*/  sqlite3_vfs_register (int /*<<< orphan*/ *,int) ; 
 void* stderr ; 
 int /*<<< orphan*/  stdin ; 
 int stdin_is_interactive ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  stifle_history (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen30 (char*) ; 
 int /*<<< orphan*/  usage (int) ; 
 int /*<<< orphan*/  write_history (char*) ; 

int main(int argc, char **argv){
  char *zErrMsg = 0;
  struct callback_data data;
  const char *zInitFile = 0;
  char *zFirstCmd = 0;
  int i;
  int rc = 0;

  if( strcmp(sqlite3_sourceid(),SQLITE_SOURCE_ID)!=0 ){
    fprintf(stderr, "SQLite header and source version mismatch\n%s\n%s\n",
            sqlite3_sourceid(), SQLITE_SOURCE_ID);
    exit(1);
  }
  Argv0 = argv[0];
  main_init(&data);
  stdin_is_interactive = isatty(0);

  /* Make sure we have a valid signal handler early, before anything
  ** else is done.
  */
#ifdef SIGINT
  signal(SIGINT, interrupt_handler);
#endif

  /* Do an initial pass through the command-line argument to locate
  ** the name of the database file, the name of the initialization file,
  ** the size of the alternative malloc heap,
  ** and the first command to execute.
  */
  for(i=1; i<argc; i++){
    char *z;
    z = argv[i];
    if( z[0]!='-' ){
      if( data.zDbFilename==0 ){
        data.zDbFilename = z;
        continue;
      }
      if( zFirstCmd==0 ){
        zFirstCmd = z;
        continue;
      }
      fprintf(stderr,"%s: Error: too many options: \"%s\"\n", Argv0, argv[i]);
      fprintf(stderr,"Use -help for a list of options.\n");
      return 1;
    }
    if( z[1]=='-' ) z++;
    if( strcmp(z,"-separator")==0
     || strcmp(z,"-nullvalue")==0
     || strcmp(z,"-cmd")==0
    ){
      (void)cmdline_option_value(argc, argv, ++i);
    }else if( strcmp(z,"-init")==0 ){
      zInitFile = cmdline_option_value(argc, argv, ++i);
    }else if( strcmp(z,"-batch")==0 ){
      /* Need to check for batch mode here to so we can avoid printing
      ** informational messages (like from process_sqliterc) before 
      ** we do the actual processing of arguments later in a second pass.
      */
      stdin_is_interactive = 0;
    }else if( strcmp(z,"-heap")==0 ){
#if defined(SQLITE_ENABLE_MEMSYS3) || defined(SQLITE_ENABLE_MEMSYS5)
      int j, c;
      const char *zSize;
      sqlite3_int64 szHeap;

      zSize = cmdline_option_value(argc, argv, ++i);
      szHeap = integerValue(zSize);
      if( szHeap>0x7fff0000 ) szHeap = 0x7fff0000;
      sqlite3_config(SQLITE_CONFIG_HEAP, malloc((int)szHeap), (int)szHeap, 64);
#endif
#ifdef SQLITE_ENABLE_VFSTRACE
    }else if( strcmp(z,"-vfstrace")==0 ){
      extern int vfstrace_register(
         const char *zTraceName,
         const char *zOldVfsName,
         int (*xOut)(const char*,void*),
         void *pOutArg,
         int makeDefault
      );
      vfstrace_register("trace",0,(int(*)(const char*,void*))fputs,stderr,1);
#endif
#ifdef SQLITE_ENABLE_MULTIPLEX
    }else if( strcmp(z,"-multiplex")==0 ){
      extern int sqlite3_multiple_initialize(const char*,int);
      sqlite3_multiplex_initialize(0, 1);
#endif
    }else if( strcmp(z,"-mmap")==0 ){
      sqlite3_int64 sz = integerValue(cmdline_option_value(argc,argv,++i));
      sqlite3_config(SQLITE_CONFIG_MMAP_SIZE, sz, sz);
    }else if( strcmp(z,"-vfs")==0 ){
      sqlite3_vfs *pVfs = sqlite3_vfs_find(cmdline_option_value(argc,argv,++i));
      if( pVfs ){
        sqlite3_vfs_register(pVfs, 1);
      }else{
        fprintf(stderr, "no such VFS: \"%s\"\n", argv[i]);
        exit(1);
      }
    }
  }
  if( data.zDbFilename==0 ){
#ifndef SQLITE_OMIT_MEMORYDB
    data.zDbFilename = ":memory:";
#else
    fprintf(stderr,"%s: Error: no database filename specified\n", Argv0);
    return 1;
#endif
  }
  data.out = stdout;

  /* Go ahead and open the database file if it already exists.  If the
  ** file does not exist, delay opening it.  This prevents empty database
  ** files from being created if a user mistypes the database name argument
  ** to the sqlite command-line tool.
  */
  if( access(data.zDbFilename, 0)==0 ){
    open_db(&data);
  }

  /* Process the initialization file if there is one.  If no -init option
  ** is given on the command line, look for a file named ~/.sqliterc and
  ** try to process it.
  */
  rc = process_sqliterc(&data,zInitFile);
  if( rc>0 ){
    return rc;
  }

  /* Make a second pass through the command-line argument and set
  ** options.  This second pass is delayed until after the initialization
  ** file is processed so that the command-line arguments will override
  ** settings in the initialization file.
  */
  for(i=1; i<argc; i++){
    char *z = argv[i];
    if( z[0]!='-' ) continue;
    if( z[1]=='-' ){ z++; }
    if( strcmp(z,"-init")==0 ){
      i++;
    }else if( strcmp(z,"-html")==0 ){
      data.mode = MODE_Html;
    }else if( strcmp(z,"-list")==0 ){
      data.mode = MODE_List;
    }else if( strcmp(z,"-line")==0 ){
      data.mode = MODE_Line;
    }else if( strcmp(z,"-column")==0 ){
      data.mode = MODE_Column;
    }else if( strcmp(z,"-csv")==0 ){
      data.mode = MODE_Csv;
      memcpy(data.separator,",",2);
    }else if( strcmp(z,"-separator")==0 ){
      sqlite3_snprintf(sizeof(data.separator), data.separator,
                       "%s",cmdline_option_value(argc,argv,++i));
    }else if( strcmp(z,"-nullvalue")==0 ){
      sqlite3_snprintf(sizeof(data.nullvalue), data.nullvalue,
                       "%s",cmdline_option_value(argc,argv,++i));
    }else if( strcmp(z,"-header")==0 ){
      data.showHeader = 1;
    }else if( strcmp(z,"-noheader")==0 ){
      data.showHeader = 0;
    }else if( strcmp(z,"-echo")==0 ){
      data.echoOn = 1;
    }else if( strcmp(z,"-stats")==0 ){
      data.statsOn = 1;
    }else if( strcmp(z,"-bail")==0 ){
      bail_on_error = 1;
    }else if( strcmp(z,"-version")==0 ){
      printf("%s %s\n", sqlite3_libversion(), sqlite3_sourceid());
      return 0;
    }else if( strcmp(z,"-interactive")==0 ){
      stdin_is_interactive = 1;
    }else if( strcmp(z,"-batch")==0 ){
      stdin_is_interactive = 0;
    }else if( strcmp(z,"-heap")==0 ){
      i++;
    }else if( strcmp(z,"-mmap")==0 ){
      i++;
    }else if( strcmp(z,"-vfs")==0 ){
      i++;
#ifdef SQLITE_ENABLE_VFSTRACE
    }else if( strcmp(z,"-vfstrace")==0 ){
      i++;
#endif
#ifdef SQLITE_ENABLE_MULTIPLEX
    }else if( strcmp(z,"-multiplex")==0 ){
      i++;
#endif
    }else if( strcmp(z,"-help")==0 ){
      usage(1);
    }else if( strcmp(z,"-cmd")==0 ){
      if( i==argc-1 ) break;
      z = cmdline_option_value(argc,argv,++i);
      if( z[0]=='.' ){
        rc = do_meta_command(z, &data);
        if( rc && bail_on_error ) return rc==2 ? 0 : rc;
      }else{
        open_db(&data);
        rc = shell_exec(data.db, z, shell_callback, &data, &zErrMsg);
        if( zErrMsg!=0 ){
          fprintf(stderr,"Error: %s\n", zErrMsg);
          if( bail_on_error ) return rc!=0 ? rc : 1;
        }else if( rc!=0 ){
          fprintf(stderr,"Error: unable to process SQL \"%s\"\n", z);
          if( bail_on_error ) return rc;
        }
      }
    }else{
      fprintf(stderr,"%s: Error: unknown option: %s\n", Argv0, z);
      fprintf(stderr,"Use -help for a list of options.\n");
      return 1;
    }
  }

  if( zFirstCmd ){
    /* Run just the command that follows the database name
    */
    if( zFirstCmd[0]=='.' ){
      rc = do_meta_command(zFirstCmd, &data);
      if( rc==2 ) rc = 0;
    }else{
      open_db(&data);
      rc = shell_exec(data.db, zFirstCmd, shell_callback, &data, &zErrMsg);
      if( zErrMsg!=0 ){
        fprintf(stderr,"Error: %s\n", zErrMsg);
        return rc!=0 ? rc : 1;
      }else if( rc!=0 ){
        fprintf(stderr,"Error: unable to process SQL \"%s\"\n", zFirstCmd);
        return rc;
      }
    }
  }else{
    /* Run commands received from standard input
    */
    if( stdin_is_interactive ){
      char *zHome;
      char *zHistory = 0;
      int nHistory;
      printf(
        "SQLite version %s %.19s\n" /*extra-version-info*/
        "Enter \".help\" for instructions\n"
        "Enter SQL statements terminated with a \";\"\n",
        sqlite3_libversion(), sqlite3_sourceid()
      );
      zHome = find_home_dir();
      if( zHome ){
        nHistory = strlen30(zHome) + 20;
        if( (zHistory = malloc(nHistory))!=0 ){
          sqlite3_snprintf(nHistory, zHistory,"%s/.sqlite_history", zHome);
        }
      }
#if defined(HAVE_READLINE) && HAVE_READLINE==1
      if( zHistory ) read_history(zHistory);
#endif
      rc = process_input(&data, 0);
      if( zHistory ){
        stifle_history(100);
        write_history(zHistory);
        free(zHistory);
      }
    }else{
      rc = process_input(&data, stdin);
    }
  }
  set_table_name(&data, 0);
  if( data.db ){
    sqlite3_close(data.db);
  }
  return rc;
}