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
typedef  int /*<<< orphan*/  temp ;
struct TYPE_2__ {char const* name; } ;
typedef  int OutputFormat ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  OUTPUT_BORLAND_DEF 130 
#define  OUTPUT_WATCOM_LBC 129 
#define  OUTPUT_WINDOWS_DEF 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int num_names ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 TYPE_1__* the_names ; 

__attribute__((used)) static void
names_dump( FILE*         out,
            OutputFormat  format,
            const char*   dll_name )
{
  int  nn;


  switch ( format )
  {
    case OUTPUT_WINDOWS_DEF:
      if ( dll_name )
        fprintf( out, "LIBRARY %s\n", dll_name );

      fprintf( out, "DESCRIPTION  FreeType 2 DLL\n" );
      fprintf( out, "EXPORTS\n" );
      for ( nn = 0; nn < num_names; nn++ )
        fprintf( out, "  %s\n", the_names[nn].name );
      break;

    case OUTPUT_BORLAND_DEF:
      if ( dll_name )
        fprintf( out, "LIBRARY %s\n", dll_name );

      fprintf( out, "DESCRIPTION  FreeType 2 DLL\n" );
      fprintf( out, "EXPORTS\n" );
      for ( nn = 0; nn < num_names; nn++ )
        fprintf( out, "  _%s\n", the_names[nn].name );
      break;

    case OUTPUT_WATCOM_LBC:
      {
        /* we must omit the .dll suffix from the library name */
        char         temp[512];
        const char*  dot;


        if ( dll_name == NULL )
        {
          fprintf( stderr,
                   "you must provide a DLL name with the -d option!\n" );
          exit( 4 );
        }

        dot = strchr( dll_name, '.' );
        if ( dot != NULL )
        {
          int  len = dot - dll_name;


          if ( len > (int)( sizeof( temp ) - 1 ) )
            len = sizeof ( temp ) - 1;

          memcpy( temp, dll_name, len );
          temp[len] = 0;

          dll_name = (const char*)temp;
        }

        for ( nn = 0; nn < num_names; nn++ )
          fprintf( out, "++_%s.%s.%s\n", the_names[nn].name, dll_name,
                        the_names[nn].name );
      }
      break;

    default:  /* LIST */
      for ( nn = 0; nn < num_names; nn++ )
        fprintf( out, "%s\n", the_names[nn].name );
  }
}