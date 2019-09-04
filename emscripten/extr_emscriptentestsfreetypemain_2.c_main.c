#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* glyph; } ;
struct TYPE_9__ {scalar_t__ bitmap_top; int /*<<< orphan*/  bitmap_left; int /*<<< orphan*/  bitmap; } ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  int /*<<< orphan*/  FT_Library ;
typedef  TYPE_1__* FT_GlyphSlot ;
typedef  TYPE_2__* FT_Face ;
typedef  int FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Face (TYPE_2__*) ; 
 int /*<<< orphan*/  FT_Done_FreeType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_Get_Char_Index (TYPE_2__*,char) ; 
 int FT_Init_FreeType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_LOAD_NO_BITMAP ; 
 int FT_Load_Glyph (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FT_New_Face (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  FT_RENDER_MODE_NORMAL ; 
 int FT_Render_Glyph (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int FT_Set_Char_Size (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HEIGHT ; 
 int WIDTH ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  draw_bitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 unsigned char* image ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  show_image () ; 
 int /*<<< orphan*/  stderr ; 

int
main( int     argc,
      char**  argv )
{
  FT_Library    library;
  FT_Face       face;

  FT_GlyphSlot  slot;
  FT_Error      error;

  FT_UInt glyphIndex;

  char*         filename;
  char*         text;

  int           target_height;

  if ( argc != 6 )
  {
    fprintf ( stderr, "usage: %s font sample-text width height angle\n", argv[0] );
    exit( 1 );
  }

  // Only test the character 'w'
  text = (char*)"w";
  
  filename      = argv[1];                           /* first argument     */
  WIDTH         = atoi(argv[3]);
  HEIGHT        = atoi(argv[4]);
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
  error = FT_Set_Char_Size( face, 0, 32 * 64, 0, 0 );                /* set character size */
  if (error) printf("Set_Cshar_Size Error! %d\n", error);
  	
  slot = face->glyph;

  glyphIndex = FT_Get_Char_Index(face, text[0]);
	
  /* load glyph image into the slot (erase previous one) */
  error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_NO_BITMAP);
  if(error) printf("FT_Load_Glyph Error! %d\n", error);
  	
  error = FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
  if(error) printf("FT_Render_Glyph Error! %d\n", error);
  	
  /* now, draw to our target surface (convert position) */
  draw_bitmap(&slot->bitmap, slot->bitmap_left, target_height - slot->bitmap_top);
  	
  show_image();
  	
  FT_Done_Face(face);
  FT_Done_FreeType(library);
  return 0;
}