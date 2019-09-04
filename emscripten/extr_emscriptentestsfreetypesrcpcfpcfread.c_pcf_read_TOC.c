#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  memory; } ;
struct TYPE_12__ {scalar_t__ version; int count; scalar_t__ offset; scalar_t__ size; struct TYPE_12__* tables; } ;
struct TYPE_13__ {TYPE_1__ toc; } ;
typedef  TYPE_1__* PCF_Toc ;
typedef  TYPE_1__ PCF_TableRec ;
typedef  TYPE_1__* PCF_Table ;
typedef  TYPE_4__* PCF_Face ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int FT_ARRAY_MAX (TYPE_1__*) ; 
 TYPE_9__* FT_FACE (TYPE_4__*) ; 
 int /*<<< orphan*/  FT_FREE (TYPE_1__*) ; 
 scalar_t__ FT_NEW_ARRAY (TYPE_1__*,int) ; 
 scalar_t__ FT_STREAM_READ_FIELDS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ FT_STREAM_SEEK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCF_Err_Cannot_Open_Resource ; 
 int /*<<< orphan*/  PCF_Err_Invalid_File_Format ; 
 int /*<<< orphan*/  PCF_Err_Invalid_Offset ; 
 int /*<<< orphan*/  PCF_Err_Ok ; 
 int /*<<< orphan*/  PCF_Err_Out_Of_Memory ; 
 scalar_t__ PCF_FILE_VERSION ; 
 int /*<<< orphan*/  pcf_table_header ; 
 int /*<<< orphan*/  pcf_toc_header ; 

__attribute__((used)) static FT_Error
  pcf_read_TOC( FT_Stream  stream,
                PCF_Face   face )
  {
    FT_Error   error;
    PCF_Toc    toc = &face->toc;
    PCF_Table  tables;

    FT_Memory  memory = FT_FACE(face)->memory;
    FT_UInt    n;


    if ( FT_STREAM_SEEK ( 0 )                          ||
         FT_STREAM_READ_FIELDS ( pcf_toc_header, toc ) )
      return PCF_Err_Cannot_Open_Resource;

    if ( toc->version != PCF_FILE_VERSION                 ||
         toc->count   >  FT_ARRAY_MAX( face->toc.tables ) ||
         toc->count   == 0                                )
      return PCF_Err_Invalid_File_Format;

    if ( FT_NEW_ARRAY( face->toc.tables, toc->count ) )
      return PCF_Err_Out_Of_Memory;

    tables = face->toc.tables;
    for ( n = 0; n < toc->count; n++ )
    {
      if ( FT_STREAM_READ_FIELDS( pcf_table_header, tables ) )
        goto Exit;
      tables++;
    }

    /* Sort tables and check for overlaps.  Because they are almost      */
    /* always ordered already, an in-place bubble sort with simultaneous */
    /* boundary checking seems appropriate.                              */
    tables = face->toc.tables;

    for ( n = 0; n < toc->count - 1; n++ )
    {
      FT_UInt  i, have_change;


      have_change = 0;

      for ( i = 0; i < toc->count - 1 - n; i++ )
      {
        PCF_TableRec  tmp;


        if ( tables[i].offset > tables[i + 1].offset )
        {
          tmp           = tables[i];
          tables[i]     = tables[i + 1];
          tables[i + 1] = tmp;

          have_change = 1;
        }

        if ( ( tables[i].size   > tables[i + 1].offset )                  ||
             ( tables[i].offset > tables[i + 1].offset - tables[i].size ) )
          return PCF_Err_Invalid_Offset;
      }

      if ( !have_change )
        break;
    }

#ifdef FT_DEBUG_LEVEL_TRACE

    {
      FT_UInt      i, j;
      const char*  name = "?";


      FT_TRACE4(( "pcf_read_TOC:\n" ));

      FT_TRACE4(( "  number of tables: %ld\n", face->toc.count ));

      tables = face->toc.tables;
      for ( i = 0; i < toc->count; i++ )
      {
        for ( j = 0; j < sizeof ( tableNames ) / sizeof ( tableNames[0] );
              j++ )
          if ( tables[i].type == (FT_UInt)( 1 << j ) )
            name = tableNames[j];

        FT_TRACE4(( "  %d: type=%s, format=0x%X, "
                    "size=%ld (0x%lX), offset=%ld (0x%lX)\n",
                    i, name,
                    tables[i].format,
                    tables[i].size, tables[i].size,
                    tables[i].offset, tables[i].offset ));
      }
    }

#endif

    return PCF_Err_Ok;

  Exit:
    FT_FREE( face->toc.tables );
    return error;
  }