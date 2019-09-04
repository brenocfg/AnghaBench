#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int const dict; scalar_t__ ident; } ;
struct TYPE_11__ {char* cursor; char* limit; void* error; } ;
struct TYPE_12__ {TYPE_1__ root; } ;
struct TYPE_13__ {int keywords_encountered; TYPE_2__ parser; } ;
typedef  TYPE_2__* T1_Parser ;
typedef  TYPE_3__* T1_Loader ;
typedef  TYPE_4__* T1_Field ;
typedef  int /*<<< orphan*/  T1_Face ;
typedef  int FT_UInt ;
typedef  int FT_PtrDist ;
typedef  int FT_Long ;
typedef  void* FT_Error ;
typedef  char FT_Byte ;
typedef  int FT_Bool ;

/* Variables and functions */
 scalar_t__ FT_ERROR_BASE (void*) ; 
 scalar_t__ FT_Err_Ignore ; 
 int /*<<< orphan*/  FT_TRACE1 (char*) ; 
 scalar_t__ IS_PS_TOKEN (char*,char*,char*) ; 
 void* T1_Err_Invalid_File_Format ; 
 void* T1_Err_Ok ; 
 int T1_FIELD_DICT_FONTDICT ; 
 int T1_FIELD_DICT_PRIVATE ; 
 int T1_FONTDIR_AFTER_PRIVATE ; 
 int T1_PRIVATE ; 
 int /*<<< orphan*/  T1_Skip_PS_Token (TYPE_2__*) ; 
 int /*<<< orphan*/  T1_Skip_Spaces (TYPE_2__*) ; 
 scalar_t__ ft_isdigit (char) ; 
 scalar_t__ ft_memcmp (char*,char*,int) ; 
 scalar_t__ ft_strcmp (char const*,char*) ; 
 scalar_t__ ft_strlen (char const*) ; 
 int /*<<< orphan*/  read_binary_data (TYPE_2__*,int*,char**) ; 
 int /*<<< orphan*/  t1_keywords ; 
 void* t1_load_keyword (int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static FT_Error
  parse_dict( T1_Face    face,
              T1_Loader  loader,
              FT_Byte*   base,
              FT_Long    size )
  {
    T1_Parser  parser = &loader->parser;
    FT_Byte   *limit, *start_binary = NULL;
    FT_Bool    have_integer = 0;


    parser->root.cursor = base;
    parser->root.limit  = base + size;
    parser->root.error  = T1_Err_Ok;

    limit = parser->root.limit;

    T1_Skip_Spaces( parser );

    while ( parser->root.cursor < limit )
    {
      FT_Byte*  cur;


      cur = parser->root.cursor;

      /* look for `eexec' */
      if ( IS_PS_TOKEN( cur, limit, "eexec" ) )
        break;

      /* look for `closefile' which ends the eexec section */
      else if ( IS_PS_TOKEN( cur, limit, "closefile" ) )
        break;

      /* in a synthetic font the base font starts after a           */
      /* `FontDictionary' token that is placed after a Private dict */
      else if ( IS_PS_TOKEN( cur, limit, "FontDirectory" ) )
      {
        if ( loader->keywords_encountered & T1_PRIVATE )
          loader->keywords_encountered |=
            T1_FONTDIR_AFTER_PRIVATE;
        parser->root.cursor += 13;
      }

      /* check whether we have an integer */
      else if ( ft_isdigit( *cur ) )
      {
        start_binary = cur;
        T1_Skip_PS_Token( parser );
        if ( parser->root.error )
          goto Exit;
        have_integer = 1;
      }

      /* in valid Type 1 fonts we don't see `RD' or `-|' directly */
      /* since those tokens are handled by parse_subrs and        */
      /* parse_charstrings                                        */
      else if ( *cur == 'R' && cur + 6 < limit && *(cur + 1) == 'D' &&
                have_integer )
      {
        FT_Long   s;
        FT_Byte*  b;


        parser->root.cursor = start_binary;
        if ( !read_binary_data( parser, &s, &b ) )
          return T1_Err_Invalid_File_Format;
        have_integer = 0;
      }

      else if ( *cur == '-' && cur + 6 < limit && *(cur + 1) == '|' &&
                have_integer )
      {
        FT_Long   s;
        FT_Byte*  b;


        parser->root.cursor = start_binary;
        if ( !read_binary_data( parser, &s, &b ) )
          return T1_Err_Invalid_File_Format;
        have_integer = 0;
      }

      /* look for immediates */
      else if ( *cur == '/' && cur + 2 < limit )
      {
        FT_PtrDist  len;


        cur++;

        parser->root.cursor = cur;
        T1_Skip_PS_Token( parser );
        if ( parser->root.error )
          goto Exit;

        len = parser->root.cursor - cur;

        if ( len > 0 && len < 22 && parser->root.cursor < limit )
        {
          /* now compare the immediate name to the keyword table */
          T1_Field  keyword = (T1_Field)t1_keywords;


          for (;;)
          {
            FT_Byte*  name;


            name = (FT_Byte*)keyword->ident;
            if ( !name )
              break;

            if ( cur[0] == name[0]                                  &&
                 len == (FT_PtrDist)ft_strlen( (const char *)name ) &&
                 ft_memcmp( cur, name, len ) == 0                   )
            {
              /* We found it -- run the parsing callback!     */
              /* We record every instance of every field      */
              /* (until we reach the base font of a           */
              /* synthetic font) to deal adequately with      */
              /* multiple master fonts; this is also          */
              /* necessary because later PostScript           */
              /* definitions override earlier ones.           */

              /* Once we encounter `FontDirectory' after      */
              /* `/Private', we know that this is a synthetic */
              /* font; except for `/CharStrings' we are not   */
              /* interested in anything that follows this     */
              /* `FontDirectory'.                             */

              /* MM fonts have more than one /Private token at */
              /* the top level; let's hope that all the junk   */
              /* that follows the first /Private token is not  */
              /* interesting to us.                            */

              /* According to Adobe Tech Note #5175 (CID-Keyed */
              /* Font Installation for ATM Software) a `begin' */
              /* must be followed by exactly one `end', and    */
              /* `begin' -- `end' pairs must be accurately     */
              /* paired.  We could use this to distinguish     */
              /* between the global Private and the Private    */
              /* dict that is a member of the Blend dict.      */

              const FT_UInt dict =
                ( loader->keywords_encountered & T1_PRIVATE )
                    ? T1_FIELD_DICT_PRIVATE
                    : T1_FIELD_DICT_FONTDICT;

              if ( !( dict & keyword->dict ) )
              {
                FT_TRACE1(( "parse_dict: found %s but ignoring it "
                            "since it is in the wrong dictionary\n",
                            keyword->ident ));
                break;
              }

              if ( !( loader->keywords_encountered &
                      T1_FONTDIR_AFTER_PRIVATE     )                  ||
                   ft_strcmp( (const char*)name, "CharStrings" ) == 0 )
              {
                parser->root.error = t1_load_keyword( face,
                                                      loader,
                                                      keyword );
                if ( parser->root.error != T1_Err_Ok )
                {
                  if ( FT_ERROR_BASE( parser->root.error ) == FT_Err_Ignore )
                    parser->root.error = T1_Err_Ok;
                  else
                    return parser->root.error;
                }
              }
              break;
            }

            keyword++;
          }
        }

        have_integer = 0;
      }
      else
      {
        T1_Skip_PS_Token( parser );
        if ( parser->root.error )
          goto Exit;
        have_integer = 0;
      }

      T1_Skip_Spaces( parser );
    }

  Exit:
    return parser->root.error;
  }