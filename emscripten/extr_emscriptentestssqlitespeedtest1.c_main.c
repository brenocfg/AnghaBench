#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
struct TYPE_2__ {char* zWR; char* zNN; char* zPK; int szTest; int bSqlOnly; int bExplain; int bReprepare; int bVerify; int /*<<< orphan*/  db; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_CONFIG_HEAP ; 
 int /*<<< orphan*/  SQLITE_CONFIG_LOOKASIDE ; 
 int /*<<< orphan*/  SQLITE_CONFIG_PAGECACHE ; 
 int /*<<< orphan*/  SQLITE_CONFIG_SCRATCH ; 
 int /*<<< orphan*/  SQLITE_DBCONFIG_LOOKASIDE ; 
 int /*<<< orphan*/  SQLITE_STATUS_MALLOC_SIZE ; 
 int /*<<< orphan*/  SQLITE_STATUS_MEMORY_USED ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_OVERFLOW ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_SIZE ; 
 int /*<<< orphan*/  SQLITE_STATUS_SCRATCH_OVERFLOW ; 
 int /*<<< orphan*/  SQLITE_STATUS_SCRATCH_SIZE ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 TYPE_1__ g ; 
 void* integerValue (char*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  randomFunc1 ; 
 int /*<<< orphan*/  speedtest1_exec (char*,...) ; 
 int /*<<< orphan*/  speedtest1_final () ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ ) ; 
 int sqlite3_config (int /*<<< orphan*/ ,void*,int,...) ; 
 int /*<<< orphan*/  sqlite3_create_function (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_db_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int) ; 
 scalar_t__ sqlite3_open (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_status (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  testset_cte () ; 
 int /*<<< orphan*/  testset_debug1 () ; 
 int /*<<< orphan*/  testset_main () ; 
 int /*<<< orphan*/  testset_rtree (int,int) ; 
 int /*<<< orphan*/  traceCallback ; 
 char* zHelp ; 

int main(int argc, char **argv){
  int doAutovac = 0;            /* True for --autovacuum */
  int cacheSize = 0;            /* Desired cache size.  0 means default */
  int doExclusive = 0;          /* True for --exclusive */
  int nHeap = 0, mnHeap = 0;    /* Heap size from --heap */
  int doIncrvac = 0;            /* True for --incrvacuum */
  const char *zJMode = 0;       /* Journal mode */
  const char *zKey = 0;         /* Encryption key */
  int nLook = 0, szLook = 0;    /* --lookaside configuration */
  int noSync = 0;               /* True for --nosync */
  int pageSize = 0;             /* Desired page size.  0 means default */
  int nPCache = 0, szPCache = 0;/* --pcache configuration */
  int nScratch = 0, szScratch=0;/* --scratch configuration */
  int showStats = 0;            /* True for --stats */
  const char *zTSet = "main";   /* Which --testset torun */
  int doTrace = 0;              /* True for --trace */
  const char *zEncoding = 0;    /* --utf16be or --utf16le */
  const char *zDbName = 0;      /* Name of the test database */

  void *pHeap = 0;              /* Allocated heap space */
  void *pLook = 0;              /* Allocated lookaside space */
  void *pPCache = 0;            /* Allocated storage for pcache */
  void *pScratch = 0;           /* Allocated storage for scratch */
  int iCur, iHi;                /* Stats values, current and "highwater" */
  int i;                        /* Loop counter */
  int rc;                       /* API return code */

  /* Process command-line arguments */
  g.zWR = "";
  g.zNN = "";
  g.zPK = "UNIQUE";
  g.szTest = 100;

  /* Emscripten commandline argument processing - first arg is ours */
  int arg = argc > 1 ? argv[1][0] - '0' : 3;
  switch(arg) {
    case 0: return 0; break;
    case 1: arg = 5; break;
    case 2: arg = 10; break;
    case 3: arg = 20; break;
    case 4: arg = 40; break;
    case 5: arg = 80; break;
    default:
      printf("error: %d\\n", arg);
      return -1;
  }
  g.szTest = arg;

  /* Back to sqlite - after the first is theirs*/
  for(i=2; i<argc; i++){
    const char *z = argv[i];
    if( z[0]=='-' ){
      do{ z++; }while( z[0]=='-' );
      if( strcmp(z,"autovacuum")==0 ){
        doAutovac = 1;
      }else if( strcmp(z,"cachesize")==0 ){
        if( i>=argc-1 ) fatal_error("missing argument on %s\n", argv[i]);
        i++;
        cacheSize = integerValue(argv[i]);
      }else if( strcmp(z,"exclusive")==0 ){
        doExclusive = 1;
      }else if( strcmp(z,"explain")==0 ){
        g.bSqlOnly = 1;
        g.bExplain = 1;
      }else if( strcmp(z,"heap")==0 ){
        if( i>=argc-2 ) fatal_error("missing arguments on %s\n", argv[i]);
        nHeap = integerValue(argv[i+1]);
        mnHeap = integerValue(argv[i+2]);
        i += 2;
      }else if( strcmp(z,"incrvacuum")==0 ){
        doIncrvac = 1;
      }else if( strcmp(z,"journal")==0 ){
        if( i>=argc-1 ) fatal_error("missing argument on %s\n", argv[i]);
        zJMode = argv[++i];
      }else if( strcmp(z,"key")==0 ){
        if( i>=argc-1 ) fatal_error("missing argument on %s\n", argv[i]);
        zKey = argv[++i];
      }else if( strcmp(z,"lookaside")==0 ){
        if( i>=argc-2 ) fatal_error("missing arguments on %s\n", argv[i]);
        nLook = integerValue(argv[i+1]);
        szLook = integerValue(argv[i+2]);
        i += 2;
      }else if( strcmp(z,"nosync")==0 ){
        noSync = 1;
      }else if( strcmp(z,"notnull")==0 ){
        g.zNN = "NOT NULL";
      }else if( strcmp(z,"pagesize")==0 ){
        if( i>=argc-1 ) fatal_error("missing argument on %s\n", argv[i]);
        pageSize = integerValue(argv[++i]);
      }else if( strcmp(z,"pcache")==0 ){
        if( i>=argc-2 ) fatal_error("missing arguments on %s\n", argv[i]);
        nPCache = integerValue(argv[i+1]);
        szPCache = integerValue(argv[i+2]);
        i += 2;
      }else if( strcmp(z,"primarykey")==0 ){
        g.zPK = "PRIMARY KEY";
      }else if( strcmp(z,"reprepare")==0 ){
        g.bReprepare = 1;
      }else if( strcmp(z,"scratch")==0 ){
        if( i>=argc-2 ) fatal_error("missing arguments on %s\n", argv[i]);
        nScratch = integerValue(argv[i+1]);
        szScratch = integerValue(argv[i+2]);
        i += 2;
      }else if( strcmp(z,"sqlonly")==0 ){
        g.bSqlOnly = 1;
      }else if( strcmp(z,"size")==0 ){
        if( i>=argc-1 ) fatal_error("missing argument on %s\n", argv[i]);
        g.szTest = integerValue(argv[++i]);
      }else if( strcmp(z,"stats")==0 ){
        showStats = 1;
      }else if( strcmp(z,"testset")==0 ){
        if( i>=argc-1 ) fatal_error("missing argument on %s\n", argv[i]);
        zTSet = argv[++i];
      }else if( strcmp(z,"trace")==0 ){
        doTrace = 1;
      }else if( strcmp(z,"utf16le")==0 ){
        zEncoding = "utf16le";
      }else if( strcmp(z,"utf16be")==0 ){
        zEncoding = "utf16be";
      }else if( strcmp(z,"verify")==0 ){
        g.bVerify = 1;
      }else if( strcmp(z,"without-rowid")==0 ){
        g.zWR = "WITHOUT ROWID";
        g.zPK = "PRIMARY KEY";
      }else if( strcmp(z, "help")==0 || strcmp(z,"?")==0 ){
        printf(zHelp, argv[0]);
        exit(0);
      }else{
        fatal_error("unknown option: %s\nUse \"%s -?\" for help\n",
                    argv[i], argv[0]);
      }
    }else if( zDbName==0 ){
      zDbName = argv[i];
    }else{
      fatal_error("surplus argument: %s\nUse \"%s -?\" for help\n",
                  argv[i], argv[0]);
    }
  }
#if 0
  if( zDbName==0 ){
    fatal_error(zHelp, argv[0]);
  }
#endif
  if( nHeap>0 ){
    pHeap = malloc( nHeap );
    if( pHeap==0 ) fatal_error("cannot allocate %d-byte heap\n", nHeap);
    rc = sqlite3_config(SQLITE_CONFIG_HEAP, pHeap, nHeap, mnHeap);
    if( rc ) fatal_error("heap configuration failed: %d\n", rc);
  }
  if( nPCache>0 && szPCache>0 ){
    pPCache = malloc( nPCache*(sqlite3_int64)szPCache );
    if( pPCache==0 ) fatal_error("cannot allocate %lld-byte pcache\n",
                                 nPCache*(sqlite3_int64)szPCache);
    rc = sqlite3_config(SQLITE_CONFIG_PAGECACHE, pPCache, szPCache, nPCache);
    if( rc ) fatal_error("pcache configuration failed: %d\n", rc);
  }
  if( nScratch>0 && szScratch>0 ){
    pScratch = malloc( nScratch*(sqlite3_int64)szScratch );
    if( pScratch==0 ) fatal_error("cannot allocate %lld-byte scratch\n",
                                 nScratch*(sqlite3_int64)szScratch);
    rc = sqlite3_config(SQLITE_CONFIG_SCRATCH, pScratch, szScratch, nScratch);
    if( rc ) fatal_error("scratch configuration failed: %d\n", rc);
  }
  if( nLook>0 ){
    sqlite3_config(SQLITE_CONFIG_LOOKASIDE, 0, 0);
  }
 
  /* Open the database and the input file */
  if( sqlite3_open(":memory:", &g.db) ){
    fatal_error("Cannot open database file: %s\n", zDbName);
  }
  if( nLook>0 && szLook>0 ){
    pLook = malloc( nLook*szLook );
    rc = sqlite3_db_config(g.db, SQLITE_DBCONFIG_LOOKASIDE, pLook, szLook,nLook);
    if( rc ) fatal_error("lookaside configuration failed: %d\n", rc);
  }

  /* Set database connection options */
  sqlite3_create_function(g.db, "random", 0, SQLITE_UTF8, 0, randomFunc1, 0, 0);
  if( doTrace ) sqlite3_trace(g.db, traceCallback, 0);
  if( zKey ){
    speedtest1_exec("PRAGMA key('%s')", zKey);
  }
  if( zEncoding ){
    speedtest1_exec("PRAGMA encoding=%s", zEncoding);
  }
  if( doAutovac ){
    speedtest1_exec("PRAGMA auto_vacuum=FULL");
  }else if( doIncrvac ){
    speedtest1_exec("PRAGMA auto_vacuum=INCREMENTAL");
  }
  if( pageSize ){
    speedtest1_exec("PRAGMA page_size=%d", pageSize);
  }
  if( cacheSize ){
    speedtest1_exec("PRAGMA cache_size=%d", cacheSize);
  }
  if( noSync ) speedtest1_exec("PRAGMA synchronous=OFF");
  if( doExclusive ){
    speedtest1_exec("PRAGMA locking_mode=EXCLUSIVE");
  }
  if( zJMode ){
    speedtest1_exec("PRAGMA journal_mode=%s", zJMode);
  }

  if( g.bExplain ) printf(".explain\n.echo on\n");
  if( strcmp(zTSet,"main")==0 ){
    testset_main();
  }else if( strcmp(zTSet,"debug1")==0 ){
    testset_debug1();
  }else if( strcmp(zTSet,"cte")==0 ){
    testset_cte();
  }else if( strcmp(zTSet,"rtree")==0 ){
    testset_rtree(6, 147);
  }else{
    fatal_error("unknown testset: \"%s\"\nChoices: main debug1 cte rtree\n",
                 zTSet);
  }
  speedtest1_final();

  /* Database connection statistics printed after both prepared statements
  ** have been finalized */
#if SQLITE_VERSION_NUMBER>=3007009
  if( showStats ){
    sqlite3_db_status(g.db, SQLITE_DBSTATUS_LOOKASIDE_USED, &iCur, &iHi, 0);
    printf("-- Lookaside Slots Used:        %d (max %d)\n", iCur,iHi);
    sqlite3_db_status(g.db, SQLITE_DBSTATUS_LOOKASIDE_HIT, &iCur, &iHi, 0);
    printf("-- Successful lookasides:       %d\n", iHi);
    sqlite3_db_status(g.db, SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE, &iCur,&iHi,0);
    printf("-- Lookaside size faults:       %d\n", iHi);
    sqlite3_db_status(g.db, SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL, &iCur,&iHi,0);
    printf("-- Lookaside OOM faults:        %d\n", iHi);
    sqlite3_db_status(g.db, SQLITE_DBSTATUS_CACHE_USED, &iCur, &iHi, 0);
    printf("-- Pager Heap Usage:            %d bytes\n", iCur);
    sqlite3_db_status(g.db, SQLITE_DBSTATUS_CACHE_HIT, &iCur, &iHi, 1);
    printf("-- Page cache hits:             %d\n", iCur);
    sqlite3_db_status(g.db, SQLITE_DBSTATUS_CACHE_MISS, &iCur, &iHi, 1);
    printf("-- Page cache misses:           %d\n", iCur);
#if SQLITE_VERSION_NUMBER>=3007012
    sqlite3_db_status(g.db, SQLITE_DBSTATUS_CACHE_WRITE, &iCur, &iHi, 1);
    printf("-- Page cache writes:           %d\n", iCur); 
#endif
    sqlite3_db_status(g.db, SQLITE_DBSTATUS_SCHEMA_USED, &iCur, &iHi, 0);
    printf("-- Schema Heap Usage:           %d bytes\n", iCur); 
    sqlite3_db_status(g.db, SQLITE_DBSTATUS_STMT_USED, &iCur, &iHi, 0);
    printf("-- Statement Heap Usage:        %d bytes\n", iCur); 
  }
#endif

  sqlite3_close(g.db);

  /* Global memory usage statistics printed after the database connection
  ** has closed.  Memory usage should be zero at this point. */
  if( showStats ){
    sqlite3_status(SQLITE_STATUS_MEMORY_USED, &iCur, &iHi, 0);
    printf("-- Memory Used (bytes):         %d (max %d)\n", iCur,iHi);
#if SQLITE_VERSION_NUMBER>=3007000
    sqlite3_status(SQLITE_STATUS_MALLOC_COUNT, &iCur, &iHi, 0);
    printf("-- Outstanding Allocations:     %d (max %d)\n", iCur,iHi);
#endif
    sqlite3_status(SQLITE_STATUS_PAGECACHE_OVERFLOW, &iCur, &iHi, 0);
    printf("-- Pcache Overflow Bytes:       %d (max %d)\n", iCur,iHi);
    sqlite3_status(SQLITE_STATUS_SCRATCH_OVERFLOW, &iCur, &iHi, 0);
    printf("-- Scratch Overflow Bytes:      %d (max %d)\n", iCur,iHi);
    sqlite3_status(SQLITE_STATUS_MALLOC_SIZE, &iCur, &iHi, 0);
    printf("-- Largest Allocation:          %d bytes\n",iHi);
    sqlite3_status(SQLITE_STATUS_PAGECACHE_SIZE, &iCur, &iHi, 0);
    printf("-- Largest Pcache Allocation:   %d bytes\n",iHi);
    sqlite3_status(SQLITE_STATUS_SCRATCH_SIZE, &iCur, &iHi, 0);
    printf("-- Largest Scratch Allocation:  %d bytes\n", iHi);
  }

  /* Release memory */
  free( pLook );
  free( pPCache );
  free( pScratch );
  free( pHeap );
  return 0;
}