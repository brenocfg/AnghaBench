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
 char** default_dir_list ; 
 char** default_ext_list ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
  usage( FILE*  out,
         char*  name )
  {
    char**  d = default_dir_list;
    char**  e = default_ext_list;


    fprintf( out, "%s [options] -- Generate random erroneous fonts\n"
                  "  and attempt to parse them with FreeType.\n\n", name );

    fprintf( out, "  --all                    All non-directory files are assumed to be fonts.\n" );
    fprintf( out, "  --check-outlines         Make sure we can parse the outlines of each glyph.\n" );
    fprintf( out, "  --dir <path>             Append <path> to list of font search directories\n"
                  "                           (no recursive search).\n" );
    fprintf( out, "  --error-count <cnt>      Introduce <cnt> single byte errors into each font\n"
                  "                           (default: 1)\n" );
    fprintf( out, "  --error-fraction <frac>  Introduce <frac>*filesize single byte errors\n"
                  "                           into each font (default: 0.0).\n" );
    fprintf( out, "  --ext <ext>              Add <ext> to list of extensions indicating fonts.\n" );
    fprintf( out, "  --help                   Print this.\n" );
    fprintf( out, "  --nohints                Turn off hinting.\n" );
    fprintf( out, "  --rasterize              Attempt to rasterize each glyph.\n" );
    fprintf( out, "  --results <path>         Place the created test fonts into <path>\n"
                  "                           (default: `results')\n" );
    fprintf( out, "  --size <float>           Use the given font size for the tests.\n" );
    fprintf( out, "  --test <file>            Run a single test on an already existing file.\n" );
    fprintf( out, "\n" );

    fprintf( out, "Default font extensions:\n" );
    fprintf( out, " " );
    while ( *e )
      fprintf( out, " .%s", *e++ );
    fprintf( out, "\n" );

    fprintf( out, "Default font directories:\n" );
    fprintf( out, " " );
    while ( *d )
      fprintf( out, " %s", *d++ );
    fprintf( out, "\n" );
  }