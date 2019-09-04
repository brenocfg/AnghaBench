#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int num_faces; } ;
struct TYPE_28__ {TYPE_7__* font; TYPE_1__ root; } ;
struct TYPE_22__ {scalar_t__ avg_width; scalar_t__ max_width; int weight; int pixel_height; int nominal_point_size; int horizontal_resolution; int vertical_resolution; scalar_t__ charset; scalar_t__ face_name_offset; scalar_t__ file_size; scalar_t__ first_char; scalar_t__ last_char; scalar_t__ external_leading; scalar_t__ italic; } ;
struct TYPE_27__ {char* family_name; scalar_t__ fnt_frame; TYPE_2__ header; int /*<<< orphan*/  fnt_size; scalar_t__ offset; } ;
struct TYPE_26__ {scalar_t__ width; int size; int y_ppem; int x_ppem; scalar_t__ height; } ;
struct TYPE_25__ {int /*<<< orphan*/  platform_id; int /*<<< orphan*/  encoding; TYPE_4__* face; int /*<<< orphan*/  encoding_id; } ;
struct TYPE_24__ {int face_flags; int style_flags; int num_fixed_sizes; char* family_name; char* style_name; scalar_t__ num_glyphs; int /*<<< orphan*/ * charmaps; int /*<<< orphan*/  charmap; scalar_t__ num_charmaps; TYPE_6__* available_sizes; scalar_t__ face_index; } ;
struct TYPE_23__ {int /*<<< orphan*/  size; } ;
typedef  int FT_UShort ;
typedef  TYPE_3__* FT_Stream ;
typedef  scalar_t__ FT_Short ;
typedef  int FT_PtrDist ;
typedef  int /*<<< orphan*/  FT_Parameter ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Int ;
typedef  TYPE_4__* FT_Face ;
typedef  scalar_t__ FT_Error ;
typedef  TYPE_5__ FT_CharMapRec ;
typedef  TYPE_6__ FT_Bitmap_Size ;
typedef  TYPE_7__* FNT_Font ;
typedef  TYPE_8__* FNT_Face ;

/* Variables and functions */
 scalar_t__ FNT_Err_Invalid_Argument ; 
 scalar_t__ FNT_Err_Invalid_File_Format ; 
 scalar_t__ FNT_Err_Unknown_File_Format ; 
 int /*<<< orphan*/  FNT_Face_Done (TYPE_8__*) ; 
 scalar_t__ FT_ALLOC (char*,int) ; 
 scalar_t__ FT_CMap_New (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_ENCODING_APPLE_ROMAN ; 
 int /*<<< orphan*/  FT_ENCODING_NONE ; 
 TYPE_4__* FT_FACE (TYPE_8__*) ; 
 int FT_FACE_FLAG_FIXED_SIZES ; 
 int FT_FACE_FLAG_FIXED_WIDTH ; 
 int FT_FACE_FLAG_HORIZONTAL ; 
 int /*<<< orphan*/  FT_FACE_MEMORY (TYPE_8__*) ; 
 int /*<<< orphan*/  FT_MEM_COPY (char*,scalar_t__,int) ; 
 void* FT_MulDiv (int,int,int) ; 
 scalar_t__ FT_NEW (TYPE_7__*) ; 
 scalar_t__ FT_NEW_ARRAY (TYPE_6__*,int) ; 
 void* FT_PIX_ROUND (int) ; 
 scalar_t__ FT_REALLOC (char*,int,scalar_t__) ; 
 int FT_STYLE_FLAG_BOLD ; 
 int FT_STYLE_FLAG_ITALIC ; 
 int /*<<< orphan*/  FT_TRACE2 (char*) ; 
 int /*<<< orphan*/  FT_UNUSED (scalar_t__) ; 
 scalar_t__ FT_WinFNT_ID_MAC ; 
 int /*<<< orphan*/  TT_APPLE_ID_DEFAULT ; 
 int /*<<< orphan*/  TT_PLATFORM_APPLE_UNICODE ; 
 int /*<<< orphan*/  TT_PLATFORM_MACINTOSH ; 
 int /*<<< orphan*/  fnt_cmap_class ; 
 scalar_t__ fnt_face_get_dll_font (TYPE_8__*,scalar_t__) ; 
 scalar_t__ fnt_font_load (TYPE_7__*,TYPE_3__*) ; 
 scalar_t__ ft_strlen (char*) ; 

__attribute__((used)) static FT_Error
  FNT_Face_Init( FT_Stream      stream,
                 FNT_Face       face,
                 FT_Int         face_index,
                 FT_Int         num_params,
                 FT_Parameter*  params )
  {
    FT_Error   error;
    FT_Memory  memory = FT_FACE_MEMORY( face );

    FT_UNUSED( num_params );
    FT_UNUSED( params );


    /* try to load font from a DLL */
    error = fnt_face_get_dll_font( face, face_index );
    if ( !error && face_index < 0 )
      goto Exit;

    if ( error == FNT_Err_Unknown_File_Format )
    {
      /* this didn't work; try to load a single FNT font */
      FNT_Font  font;

      if ( FT_NEW( face->font ) )
        goto Exit;

      face->root.num_faces = 1;

      font           = face->font;
      font->offset   = 0;
      font->fnt_size = stream->size;

      error = fnt_font_load( font, stream );

      if ( !error )
      {
        if ( face_index > 0 )
          error = FNT_Err_Invalid_Argument;
        else if ( face_index < 0 )
          goto Exit;
      }
    }

    if ( error )
      goto Fail;

    /* we now need to fill the root FT_Face fields */
    /* with relevant information                   */
    {
      FT_Face     root = FT_FACE( face );
      FNT_Font    font = face->font;
      FT_PtrDist  family_size;


      root->face_index = face_index;

      root->face_flags = FT_FACE_FLAG_FIXED_SIZES |
                         FT_FACE_FLAG_HORIZONTAL;

      if ( font->header.avg_width == font->header.max_width )
        root->face_flags |= FT_FACE_FLAG_FIXED_WIDTH;

      if ( font->header.italic )
        root->style_flags |= FT_STYLE_FLAG_ITALIC;

      if ( font->header.weight >= 800 )
        root->style_flags |= FT_STYLE_FLAG_BOLD;

      /* set up the `fixed_sizes' array */
      if ( FT_NEW_ARRAY( root->available_sizes, 1 ) )
        goto Fail;

      root->num_fixed_sizes = 1;

      {
        FT_Bitmap_Size*  bsize = root->available_sizes;
        FT_UShort        x_res, y_res;


        bsize->width  = font->header.avg_width;
        bsize->height = (FT_Short)(
          font->header.pixel_height + font->header.external_leading );
        bsize->size   = font->header.nominal_point_size << 6;

        x_res = font->header.horizontal_resolution;
        if ( !x_res )
          x_res = 72;

        y_res = font->header.vertical_resolution;
        if ( !y_res )
          y_res = 72;

        bsize->y_ppem = FT_MulDiv( bsize->size, y_res, 72 );
        bsize->y_ppem = FT_PIX_ROUND( bsize->y_ppem );

        /*
         * this reads:
         *
         * the nominal height is larger than the bbox's height
         *
         * => nominal_point_size contains incorrect value;
         *    use pixel_height as the nominal height
         */
        if ( bsize->y_ppem > ( font->header.pixel_height << 6 ) )
        {
          FT_TRACE2(( "use pixel_height as the nominal height\n" ));

          bsize->y_ppem = font->header.pixel_height << 6;
          bsize->size   = FT_MulDiv( bsize->y_ppem, 72, y_res );
        }

        bsize->x_ppem = FT_MulDiv( bsize->size, x_res, 72 );
        bsize->x_ppem = FT_PIX_ROUND( bsize->x_ppem );
      }

      {
        FT_CharMapRec  charmap;


        charmap.encoding    = FT_ENCODING_NONE;
        /* initial platform/encoding should indicate unset status? */
        charmap.platform_id = TT_PLATFORM_APPLE_UNICODE;
        charmap.encoding_id = TT_APPLE_ID_DEFAULT;
        charmap.face        = root;

        if ( font->header.charset == FT_WinFNT_ID_MAC )
        {
          charmap.encoding    = FT_ENCODING_APPLE_ROMAN;
          charmap.platform_id = TT_PLATFORM_MACINTOSH;
/*        charmap.encoding_id = TT_MAC_ID_ROMAN; */
        }

        error = FT_CMap_New( fnt_cmap_class,
                             NULL,
                             &charmap,
                             NULL );
        if ( error )
          goto Fail;

        /* Select default charmap */
        if ( root->num_charmaps )
          root->charmap = root->charmaps[0];
      }

      /* setup remaining flags */

      /* reserve one slot for the .notdef glyph at index 0 */
      root->num_glyphs = font->header.last_char -
                         font->header.first_char + 1 + 1;

      if ( font->header.face_name_offset >= font->header.file_size )
      {
        FT_TRACE2(( "invalid family name offset\n" ));
        error = FNT_Err_Invalid_File_Format;
        goto Fail;
      }
      family_size = font->header.file_size - font->header.face_name_offset;
      /* Some broken fonts don't delimit the face name with a final */
      /* NULL byte -- the frame is erroneously one byte too small.  */
      /* We thus allocate one more byte, setting it explicitly to   */
      /* zero.                                                      */
      if ( FT_ALLOC( font->family_name, family_size + 1 ) )
        goto Fail;

      FT_MEM_COPY( font->family_name,
                   font->fnt_frame + font->header.face_name_offset,
                   family_size );

      font->family_name[family_size] = '\0';

      if ( FT_REALLOC( font->family_name,
                       family_size,
                       ft_strlen( font->family_name ) + 1 ) )
        goto Fail;

      root->family_name = font->family_name;
      root->style_name  = (char *)"Regular";

      if ( root->style_flags & FT_STYLE_FLAG_BOLD )
      {
        if ( root->style_flags & FT_STYLE_FLAG_ITALIC )
          root->style_name = (char *)"Bold Italic";
        else
          root->style_name = (char *)"Bold";
      }
      else if ( root->style_flags & FT_STYLE_FLAG_ITALIC )
        root->style_name = (char *)"Italic";
    }
    goto Exit;

  Fail:
    FNT_Face_Done( face );

  Exit:
    return error;
  }