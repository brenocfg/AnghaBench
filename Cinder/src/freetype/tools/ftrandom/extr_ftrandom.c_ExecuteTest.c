#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_faces; } ;
typedef  int /*<<< orphan*/  FT_Library ;
typedef  TYPE_1__* FT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Face (TYPE_1__*) ; 
 int /*<<< orphan*/  FT_Done_FreeType (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_Init_FreeType (int /*<<< orphan*/ *) ; 
 scalar_t__ FT_New_Face (int /*<<< orphan*/ ,char*,long,TYPE_1__**) ; 
 int /*<<< orphan*/  TestFace (TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
  ExecuteTest( char*  testfont )
  {
    FT_Library  context;
    FT_Face     face;


    if ( FT_Init_FreeType( &context ) )
    {
      fprintf( stderr, "Can't initialize FreeType.\n" );
      exit( 1 );
    }

    if ( FT_New_Face( context, testfont, 0, &face ) )
    {
      /* The font is erroneous, so if this fails that's ok. */
      exit( 0 );
    }

    if ( face->num_faces == 1 )
      TestFace( face );
    else
    {
      long  i, num;


      num = face->num_faces;
      FT_Done_Face( face );

      for ( i = 0; i < num; i++ )
      {
        if ( !FT_New_Face( context, testfont, i, &face ) )
          TestFace( face );
      }
    }

    FT_Done_FreeType( context );

    exit( 0 );
  }