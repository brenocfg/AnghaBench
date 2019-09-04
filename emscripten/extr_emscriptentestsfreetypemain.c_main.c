#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_4__* glyph; } ;
struct TYPE_13__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_16__ {TYPE_1__ advance; scalar_t__ bitmap_top; int /*<<< orphan*/  bitmap_left; int /*<<< orphan*/  bitmap; } ;
struct TYPE_15__ {void* yy; void* yx; void* xy; void* xx; } ;
struct TYPE_14__ {int x; scalar_t__ y; } ;
typedef  TYPE_2__ FT_Vector ;
typedef  TYPE_3__ FT_Matrix ;
typedef  int /*<<< orphan*/  FT_Library ;
typedef  TYPE_4__* FT_GlyphSlot ;
typedef  void* FT_Fixed ;
typedef  TYPE_5__* FT_Face ;
typedef  int FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Face (TYPE_5__*) ; 
 int /*<<< orphan*/  FT_Done_FreeType (int /*<<< orphan*/ ) ; 
 int FT_Init_FreeType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_LOAD_RENDER ; 
 int FT_Load_Char (TYPE_5__*,char,int /*<<< orphan*/ ) ; 
 int FT_New_Face (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_5__**) ; 
 int FT_Set_Char_Size (TYPE_5__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_Set_Transform (TYPE_5__*,TYPE_3__*,TYPE_2__*) ; 
 int HEIGHT ; 
 int WIDTH ; 
 int atoi (char*) ; 
 int cos (double) ; 
 int /*<<< orphan*/  draw_bitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 unsigned char* image ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  show_image () ; 
 int sin (double) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 

int
main( int     argc,
      char**  argv )
{
  FT_Library    library;
  FT_Face       face;

  FT_GlyphSlot  slot;
  FT_Matrix     matrix;                 /* transformation matrix */
  FT_Vector     pen;                    /* untransformed origin  */
  FT_Error      error;

  char*         filename;
  char*         text;

  double        angle;
  int           target_height;
  int           n, num_chars;

  if ( argc != 6 )
  {
    fprintf ( stderr, "usage: %s font sample-text width height angle\n", argv[0] );
    exit( 1 );
  }

  filename      = argv[1];                           /* first argument     */
  text          = argv[2];                           /* second argument    */
  num_chars     = strlen( text );
  WIDTH         = atoi(argv[3]);
  HEIGHT        = atoi(argv[4]);
  angle         = ( ((float)atoi(argv[5])) / 360 ) * 3.14159 * 2;      /* use 25 degrees     */
  target_height = HEIGHT;

  image = (unsigned char*)malloc(WIDTH*HEIGHT);
  for (int x = 0; x < WIDTH; x++)
    for (int y = 0; y < HEIGHT; y++)
      image[y*WIDTH + x] = 0;

  error = FT_Init_FreeType( &library );              /* initialize library */
  if (error) printf("Init Error! %d\n", error);

  error = FT_New_Face( library, argv[1], 0, &face ); /* create face object */
  if (error) printf("New_Face Error! %d\n", error);

  /* use 50pt at 100dpi */
  error = FT_Set_Char_Size( face, 50 * 64, 0,
                            100, 0 );                /* set character size */
  if (error) printf("Set_Char_Size Error! %d\n", error);

  slot = face->glyph;

  /* set up matrix */
  matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
  matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
  matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
  matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );

  pen.x = 1000;
  pen.y = 0;

  for ( n = 0; n < num_chars; n++ )
  {
    /* set transformation */
    FT_Set_Transform( face, &matrix, &pen );

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