#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* glyph; } ;
struct TYPE_9__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_11__ {TYPE_1__ advance; scalar_t__ bitmap_top; int /*<<< orphan*/  bitmap_left; int /*<<< orphan*/  bitmap; } ;
struct TYPE_10__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_2__ FT_Vector ;
typedef  int /*<<< orphan*/  FT_Library ;
typedef  TYPE_3__* FT_GlyphSlot ;
typedef  TYPE_4__* FT_Face ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Face (TYPE_4__*) ; 
 int /*<<< orphan*/  FT_Done_FreeType (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_Init_FreeType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_LOAD_RENDER ; 
 scalar_t__ FT_Load_Char (TYPE_4__*,char,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_New_Face (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_4__**) ; 
 scalar_t__ FT_Set_Char_Size (TYPE_4__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int HEIGHT ; 
 int WIDTH ; 
 int /*<<< orphan*/  draw_bitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char* image ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printError (scalar_t__) ; 
 int /*<<< orphan*/  show_image () ; 
 int strlen (char*) ; 

int
main( int     argc,
      char**  argv )
{
  FT_Library    library;
  FT_Face       face;

  FT_GlyphSlot  slot;
  FT_Vector     pen;
  FT_Error      error;

  char*         filename;
  char*         text;

  double        angle;
  int           target_height;
  int           n, num_chars;

  filename      = "LiberationSansBold.ttf";                          
  text          = "w";
  num_chars     = strlen( text );
  WIDTH         = 16;
  HEIGHT        = 16;
  target_height = HEIGHT;

  image = (unsigned char*)malloc(WIDTH*HEIGHT);
  for (int x = 0; x < WIDTH; x++)
    for (int y = 0; y < HEIGHT; y++)
      image[y*WIDTH + x] = 0;

  error = FT_Init_FreeType( &library ); /* initialize library */
  if (error) printError(error);

  error = FT_New_Face( library, filename, 0, &face ); /* create face object */
  if (error) printError(error);

  error = FT_Set_Char_Size( face, 16 * 64, 0, 100, 0 ); /* set character size */
  if (error) printError(error);

  slot = face->glyph;

  pen.x = 0;
  pen.y = 0;

  for ( n = 0; n < num_chars; n++ )
  {

    /* load glyph image into the slot (erase previous one) */
    error = FT_Load_Char( face, text[n], FT_LOAD_RENDER );
    if ( error )
      continue;                 /* ignore errors */

    /* now, draw to our target surface (convert position) */
    draw_bitmap( &slot->bitmap,
                 slot->bitmap_left,
                 target_height - slot->bitmap_top );

    /* increment pen position */
    pen.x += slot->advance.x;
    pen.y += slot->advance.y;
  }

  show_image();

  FT_Done_Face    ( face );
  FT_Done_FreeType( library );

  
  return 0;
}