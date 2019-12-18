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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  forever ;
typedef  int FT_F26Dot6 ;

/* Variables and functions */
 int /*<<< orphan*/  ExecuteTest (char*) ; 
 int /*<<< orphan*/  FindFonts (char**,char**) ; 
 char** calloc (size_t,int) ; 
 int check_outlines ; 
 char** default_dir_list ; 
 char** default_ext_list ; 
 unsigned int error_count ; 
 double error_fraction ; 
 int /*<<< orphan*/  exit (int) ; 
 int font_size ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int nohints ; 
 int rasterize ; 
 char* results_dir ; 
 int /*<<< orphan*/  srandom (unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strtod (char*,char**) ; 
 scalar_t__ strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,char*) ; 

int
  main( int     argc,
        char**  argv )
  {
    char    **dirs, **exts;
    int     dcnt = 0, ecnt = 0, rset = false, allexts = false;
    int     i;
    time_t  now;
    char*   testfile = NULL;


    dirs = calloc( (size_t)( argc + 1 ), sizeof ( char ** ) );
    exts = calloc( (size_t)( argc + 1 ), sizeof ( char ** ) );

    for ( i = 1; i < argc; i++ )
    {
      char*  pt = argv[i];
      char*  end;


      if ( pt[0] == '-' && pt[1] == '-' )
        pt++;

      if ( strcmp( pt, "-all" ) == 0 )
        allexts = true;
      else if ( strcmp( pt, "-check-outlines" ) == 0 )
        check_outlines = true;
      else if ( strcmp( pt, "-dir" ) == 0 )
        dirs[dcnt++] = argv[++i];
      else if ( strcmp( pt, "-error-count" ) == 0 )
      {
        if ( !rset )
          error_fraction = 0.0;
        rset = true;
        error_count = (unsigned int)strtoul( argv[++i], &end, 10 );
        if ( *end != '\0' )
        {
          fprintf( stderr, "Bad value for error-count: %s\n", argv[i] );
          exit( 1 );
        }
      }
      else if ( strcmp( pt, "-error-fraction" ) == 0 )
      {
        if ( !rset )
          error_count = 0;
        rset = true;
        error_fraction = strtod( argv[++i], &end );
        if ( *end != '\0' )
        {
          fprintf( stderr, "Bad value for error-fraction: %s\n", argv[i] );
          exit( 1 );
        }
        if ( error_fraction < 0.0 || error_fraction > 1.0 )
        {
          fprintf( stderr, "error-fraction must be in the range [0;1]\n" );
          exit( 1 );
        }
      }
      else if ( strcmp( pt, "-ext" ) == 0 )
        exts[ecnt++] = argv[++i];
      else if ( strcmp( pt, "-help" ) == 0 )
      {
        usage( stdout, argv[0] );
        exit( 0 );
      }
      else if ( strcmp( pt, "-nohints" ) == 0 )
        nohints = true;
      else if ( strcmp( pt, "-rasterize" ) == 0 )
        rasterize = true;
      else if ( strcmp( pt, "-results" ) == 0 )
        results_dir = argv[++i];
      else if ( strcmp( pt, "-size" ) == 0 )
      {
        font_size = (FT_F26Dot6)( strtod( argv[++i], &end ) * 64 );
        if ( *end != '\0' || font_size < 64 )
        {
          fprintf( stderr, "Bad value for size: %s\n", argv[i] );
          exit( 1 );
        }
      }
      else if ( strcmp( pt, "-test" ) == 0 )
        testfile = argv[++i];
      else
      {
        usage( stderr, argv[0] );
        exit( 1 );
      }
    }

    if ( allexts )
    {
      free( exts );
      exts = NULL;
    }
    else if ( ecnt == 0 )
    {
      free( exts );
      exts = default_ext_list;
    }

    if ( dcnt == 0 )
    {
      free( dirs );
      dirs = default_dir_list;
    }

    if ( testfile )
      ExecuteTest( testfile );         /* This should never return */

    time( &now );
    srandom( (unsigned int)now );

    FindFonts( dirs, exts );
    mkdir( results_dir, 0755 );

    forever
      do_test();

    return 0;
  }