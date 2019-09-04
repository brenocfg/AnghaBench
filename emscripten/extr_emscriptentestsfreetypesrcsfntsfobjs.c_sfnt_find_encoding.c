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
typedef  int /*<<< orphan*/  tt_encodings ;
typedef  int /*<<< orphan*/  FT_Encoding ;

/* Variables and functions */
#define  FT_ENCODING_APPLE_ROMAN 148 
#define  FT_ENCODING_BIG5 147 
#define  FT_ENCODING_GB2312 146 
#define  FT_ENCODING_JOHAB 145 
#define  FT_ENCODING_MS_SYMBOL 144 
 int /*<<< orphan*/  FT_ENCODING_NONE ; 
#define  FT_ENCODING_SJIS 143 
#define  FT_ENCODING_UNICODE 142 
#define  FT_ENCODING_WANSUNG 141 
#define  TT_MAC_ID_ROMAN 140 
#define  TT_MS_ID_BIG_5 139 
#define  TT_MS_ID_GB2312 138 
#define  TT_MS_ID_JOHAB 137 
#define  TT_MS_ID_SJIS 136 
#define  TT_MS_ID_SYMBOL_CS 135 
#define  TT_MS_ID_UCS_4 134 
#define  TT_MS_ID_UNICODE_CS 133 
#define  TT_MS_ID_WANSUNG 132 
#define  TT_PLATFORM_APPLE_UNICODE 131 
#define  TT_PLATFORM_ISO 130 
#define  TT_PLATFORM_MACINTOSH 129 
#define  TT_PLATFORM_MICROSOFT 128 

__attribute__((used)) static FT_Encoding
  sfnt_find_encoding( int  platform_id,
                      int  encoding_id )
  {
    typedef struct  TEncoding_
    {
      int          platform_id;
      int          encoding_id;
      FT_Encoding  encoding;

    } TEncoding;

    static
    const TEncoding  tt_encodings[] =
    {
      { TT_PLATFORM_ISO,           -1,                  FT_ENCODING_UNICODE },

      { TT_PLATFORM_APPLE_UNICODE, -1,                  FT_ENCODING_UNICODE },

      { TT_PLATFORM_MACINTOSH,     TT_MAC_ID_ROMAN,     FT_ENCODING_APPLE_ROMAN },

      { TT_PLATFORM_MICROSOFT,     TT_MS_ID_SYMBOL_CS,  FT_ENCODING_MS_SYMBOL },
      { TT_PLATFORM_MICROSOFT,     TT_MS_ID_UCS_4,      FT_ENCODING_UNICODE },
      { TT_PLATFORM_MICROSOFT,     TT_MS_ID_UNICODE_CS, FT_ENCODING_UNICODE },
      { TT_PLATFORM_MICROSOFT,     TT_MS_ID_SJIS,       FT_ENCODING_SJIS },
      { TT_PLATFORM_MICROSOFT,     TT_MS_ID_GB2312,     FT_ENCODING_GB2312 },
      { TT_PLATFORM_MICROSOFT,     TT_MS_ID_BIG_5,      FT_ENCODING_BIG5 },
      { TT_PLATFORM_MICROSOFT,     TT_MS_ID_WANSUNG,    FT_ENCODING_WANSUNG },
      { TT_PLATFORM_MICROSOFT,     TT_MS_ID_JOHAB,      FT_ENCODING_JOHAB }
    };

    const TEncoding  *cur, *limit;


    cur   = tt_encodings;
    limit = cur + sizeof ( tt_encodings ) / sizeof ( tt_encodings[0] );

    for ( ; cur < limit; cur++ )
    {
      if ( cur->platform_id == platform_id )
      {
        if ( cur->encoding_id == encoding_id ||
             cur->encoding_id == -1          )
          return cur->encoding;
      }
    }

    return FT_ENCODING_NONE;
  }