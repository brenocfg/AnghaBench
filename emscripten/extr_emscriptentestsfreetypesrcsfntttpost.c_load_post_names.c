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
struct TYPE_10__ {int loaded; } ;
struct TYPE_9__ {int FormatType; } ;
struct TYPE_11__ {int /*<<< orphan*/  stream; } ;
struct TYPE_12__ {TYPE_2__ postscript_names; TYPE_1__ postscript; scalar_t__ (* goto_table ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ;TYPE_3__ root; } ;
typedef  TYPE_4__* TT_Face ;
typedef  scalar_t__ FT_ULong ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  scalar_t__ FT_Long ;
typedef  int FT_Fixed ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ FT_STREAM_POS () ; 
 scalar_t__ FT_STREAM_SKIP (int) ; 
 scalar_t__ SFNT_Err_Invalid_File_Format ; 
 int /*<<< orphan*/  TTAG_post ; 
 scalar_t__ load_format_20 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ load_format_25 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static FT_Error
  load_post_names( TT_Face  face )
  {
    FT_Stream  stream;
    FT_Error   error;
    FT_Fixed   format;
    FT_ULong   post_len;
    FT_Long    post_limit;


    /* get a stream for the face's resource */
    stream = face->root.stream;

    /* seek to the beginning of the PS names table */
    error = face->goto_table( face, TTAG_post, stream, &post_len );
    if ( error )
      goto Exit;

    post_limit = FT_STREAM_POS() + post_len;

    format = face->postscript.FormatType;

    /* go to beginning of subtable */
    if ( FT_STREAM_SKIP( 32 ) )
      goto Exit;

    /* now read postscript table */
    if ( format == 0x00020000L )
      error = load_format_20( face, stream, post_limit );
    else if ( format == 0x00028000L )
      error = load_format_25( face, stream, post_limit );
    else
      error = SFNT_Err_Invalid_File_Format;

    face->postscript_names.loaded = 1;

  Exit:
    return error;
  }