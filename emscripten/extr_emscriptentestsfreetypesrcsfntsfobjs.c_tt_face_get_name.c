#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  stream; TYPE_3__* names; } ;
struct TYPE_9__ {int /*<<< orphan*/  memory; } ;
struct TYPE_12__ {scalar_t__ num_names; TYPE_2__ name_table; TYPE_1__ root; } ;
struct TYPE_11__ {scalar_t__ nameID; scalar_t__ stringLength; int platformID; int languageID; int encodingID; int /*<<< orphan*/ * string; int /*<<< orphan*/  stringOffset; } ;
typedef  int /*<<< orphan*/ * (* TT_NameEntry_ConvertFunc ) (TYPE_3__*,int /*<<< orphan*/ ) ;
typedef  TYPE_3__ TT_NameEntryRec ;
typedef  TYPE_5__* TT_Face ;
typedef  scalar_t__ FT_UShort ;
typedef  int /*<<< orphan*/  FT_String ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int FT_Int ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  scalar_t__ FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  FT_ASSERT (int /*<<< orphan*/ **) ; 
 scalar_t__ FT_BOOL (int) ; 
 int /*<<< orphan*/  FT_FREE (int /*<<< orphan*/ *) ; 
 scalar_t__ FT_QNEW_ARRAY (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ FT_STREAM_READ (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ FT_STREAM_SEEK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SFNT_Err_Ok ; 
 int TT_MAC_ID_ROMAN ; 
 int TT_MAC_LANGID_ENGLISH ; 
#define  TT_MS_ID_SYMBOL_CS 134 
#define  TT_MS_ID_UCS_4 133 
#define  TT_MS_ID_UNICODE_CS 132 
#define  TT_PLATFORM_APPLE_UNICODE 131 
#define  TT_PLATFORM_ISO 130 
#define  TT_PLATFORM_MACINTOSH 129 
#define  TT_PLATFORM_MICROSOFT 128 
 int /*<<< orphan*/ * tt_name_entry_ascii_from_other (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tt_name_entry_ascii_from_utf16 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  tt_face_get_name( TT_Face      face,
                    FT_UShort    nameid,
                    FT_String**  name )
  {
    FT_Memory         memory = face->root.memory;
    FT_Error          error  = SFNT_Err_Ok;
    FT_String*        result = NULL;
    FT_UShort         n;
    TT_NameEntryRec*  rec;
    FT_Int            found_apple         = -1;
    FT_Int            found_apple_roman   = -1;
    FT_Int            found_apple_english = -1;
    FT_Int            found_win           = -1;
    FT_Int            found_unicode       = -1;

    FT_Bool           is_english = 0;

    TT_NameEntry_ConvertFunc  convert;


    FT_ASSERT( name );

    rec = face->name_table.names;
    for ( n = 0; n < face->num_names; n++, rec++ )
    {
      /* According to the OpenType 1.3 specification, only Microsoft or  */
      /* Apple platform IDs might be used in the `name' table.  The      */
      /* `Unicode' platform is reserved for the `cmap' table, and the    */
      /* `ISO' one is deprecated.                                        */
      /*                                                                 */
      /* However, the Apple TrueType specification doesn't say the same  */
      /* thing and goes to suggest that all Unicode `name' table entries */
      /* should be coded in UTF-16 (in big-endian format I suppose).     */
      /*                                                                 */
      if ( rec->nameID == nameid && rec->stringLength > 0 )
      {
        switch ( rec->platformID )
        {
        case TT_PLATFORM_APPLE_UNICODE:
        case TT_PLATFORM_ISO:
          /* there is `languageID' to check there.  We should use this */
          /* field only as a last solution when nothing else is        */
          /* available.                                                */
          /*                                                           */
          found_unicode = n;
          break;

        case TT_PLATFORM_MACINTOSH:
          /* This is a bit special because some fonts will use either    */
          /* an English language id, or a Roman encoding id, to indicate */
          /* the English version of its font name.                       */
          /*                                                             */
          if ( rec->languageID == TT_MAC_LANGID_ENGLISH )
            found_apple_english = n;
          else if ( rec->encodingID == TT_MAC_ID_ROMAN )
            found_apple_roman = n;
          break;

        case TT_PLATFORM_MICROSOFT:
          /* we only take a non-English name when there is nothing */
          /* else available in the font                            */
          /*                                                       */
          if ( found_win == -1 || ( rec->languageID & 0x3FF ) == 0x009 )
          {
            switch ( rec->encodingID )
            {
            case TT_MS_ID_SYMBOL_CS:
            case TT_MS_ID_UNICODE_CS:
            case TT_MS_ID_UCS_4:
              is_english = FT_BOOL( ( rec->languageID & 0x3FF ) == 0x009 );
              found_win  = n;
              break;

            default:
              ;
            }
          }
          break;

        default:
          ;
        }
      }
    }

    found_apple = found_apple_roman;
    if ( found_apple_english >= 0 )
      found_apple = found_apple_english;

    /* some fonts contain invalid Unicode or Macintosh formatted entries; */
    /* we will thus favor names encoded in Windows formats if available   */
    /* (provided it is an English name)                                   */
    /*                                                                    */
    convert = NULL;
    if ( found_win >= 0 && !( found_apple >= 0 && !is_english ) )
    {
      rec = face->name_table.names + found_win;
      switch ( rec->encodingID )
      {
        /* all Unicode strings are encoded using UTF-16BE */
      case TT_MS_ID_UNICODE_CS:
      case TT_MS_ID_SYMBOL_CS:
        convert = tt_name_entry_ascii_from_utf16;
        break;

      case TT_MS_ID_UCS_4:
        /* Apparently, if this value is found in a name table entry, it is */
        /* documented as `full Unicode repertoire'.  Experience with the   */
        /* MsGothic font shipped with Windows Vista shows that this really */
        /* means UTF-16 encoded names (UCS-4 values are only used within   */
        /* charmaps).                                                      */
        convert = tt_name_entry_ascii_from_utf16;
        break;

      default:
        ;
      }
    }
    else if ( found_apple >= 0 )
    {
      rec     = face->name_table.names + found_apple;
      convert = tt_name_entry_ascii_from_other;
    }
    else if ( found_unicode >= 0 )
    {
      rec     = face->name_table.names + found_unicode;
      convert = tt_name_entry_ascii_from_utf16;
    }

    if ( rec && convert )
    {
      if ( rec->string == NULL )
      {
        FT_Stream  stream = face->name_table.stream;


        if ( FT_QNEW_ARRAY ( rec->string, rec->stringLength ) ||
             FT_STREAM_SEEK( rec->stringOffset )              ||
             FT_STREAM_READ( rec->string, rec->stringLength ) )
        {
          FT_FREE( rec->string );
          rec->stringLength = 0;
          result            = NULL;
          goto Exit;
        }
      }

      result = convert( rec, memory );
    }

  Exit:
    *name = result;
    return error;
  }