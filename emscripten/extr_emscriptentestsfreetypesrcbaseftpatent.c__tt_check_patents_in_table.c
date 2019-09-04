#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  stream; } ;
struct TYPE_7__ {scalar_t__ (* table_info ) (TYPE_2__*,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ;} ;
typedef  scalar_t__ FT_ULong ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  TYPE_1__* FT_Service_SFNT_Table ;
typedef  TYPE_2__* FT_Face ;
typedef  scalar_t__ FT_Error ;
typedef  int /*<<< orphan*/  FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FT_Err_Ok ; 
 int /*<<< orphan*/  FT_FACE_FIND_SERVICE (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_STREAM_SEEK (scalar_t__) ; 
 int /*<<< orphan*/  SFNT_TABLE ; 
 int /*<<< orphan*/  _tt_check_patents_in_range (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static FT_Bool
  _tt_check_patents_in_table( FT_Face   face,
                              FT_ULong  tag )
  {
    FT_Stream              stream = face->stream;
    FT_Error               error  = FT_Err_Ok;
    FT_Service_SFNT_Table  service;
    FT_Bool                result = FALSE;


    FT_FACE_FIND_SERVICE( face, service, SFNT_TABLE );

    if ( service )
    {
      FT_UInt   i = 0;
      FT_ULong  tag_i = 0, offset_i = 0, length_i = 0;


      for ( i = 0; !error && tag_i != tag ; i++ )
        error = service->table_info( face, i,
                                     &tag_i, &offset_i, &length_i );

      if ( error                      ||
           FT_STREAM_SEEK( offset_i ) )
        goto Exit;

      result = _tt_check_patents_in_range( stream, length_i );
    }

  Exit:
    return result;
  }