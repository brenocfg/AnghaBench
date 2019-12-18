#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ magic; int lfanew; int resource_tab_offset; int rname_tab_offset; int machine; int number_of_sections; int size_of_optional_header; int magic32; scalar_t__ rsrc_virtual_address; int name; scalar_t__ virtual_address; int pointer_to_raw_data; int number_of_named_entries; int number_of_id_entries; int offset; int offset_to_data; int size; int /*<<< orphan*/  code_page; int /*<<< orphan*/  size_of_raw_data; int /*<<< orphan*/  rsrc_size; } ;
typedef  TYPE_2__ WinPE_RsrcDirRec ;
typedef  TYPE_2__ WinPE_RsrcDirEntryRec ;
typedef  TYPE_2__ WinPE_RsrcDataEntryRec ;
typedef  TYPE_2__ WinPE32_SectionRec ;
typedef  TYPE_2__ WinPE32_HeaderRec ;
typedef  TYPE_2__ WinNE_HeaderRec ;
typedef  TYPE_2__ WinMZ_HeaderRec ;
struct TYPE_24__ {int size; scalar_t__ cursor; scalar_t__ limit; } ;
struct TYPE_22__ {int num_faces; } ;
struct TYPE_21__ {int /*<<< orphan*/  memory; TYPE_9__* stream; } ;
struct TYPE_20__ {int offset; int fnt_size; } ;
struct TYPE_19__ {TYPE_1__ root; TYPE_11__* font; } ;
typedef  int FT_UShort ;
typedef  int FT_ULong ;
typedef  TYPE_9__* FT_Stream ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int FT_Long ;
typedef  scalar_t__ FT_Int ;
typedef  scalar_t__ FT_Error ;
typedef  TYPE_10__* FNT_Face ;

/* Variables and functions */
 int FT_ABS (scalar_t__) ; 
 scalar_t__ FT_ERR (int /*<<< orphan*/ ) ; 
 TYPE_17__* FT_FACE (TYPE_10__*) ; 
 scalar_t__ FT_FRAME_ENTER (int) ; 
 int /*<<< orphan*/  FT_FRAME_EXIT () ; 
 int FT_GET_USHORT_LE () ; 
 scalar_t__ FT_NEW (TYPE_11__*) ; 
 int FT_STREAM_POS () ; 
 scalar_t__ FT_STREAM_READ_FIELDS (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ FT_STREAM_SEEK (int) ; 
 scalar_t__ FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_TRACE2 (char*) ; 
 int /*<<< orphan*/  Invalid_Argument ; 
 int /*<<< orphan*/  Invalid_File_Format ; 
 int /*<<< orphan*/  Unknown_File_Format ; 
 scalar_t__ WINFNT_MZ_MAGIC ; 
 scalar_t__ WINFNT_NE_MAGIC ; 
 scalar_t__ WINFNT_PE_MAGIC ; 
 int /*<<< orphan*/  fnt_font_done (TYPE_10__*) ; 
 scalar_t__ fnt_font_load (TYPE_11__*,TYPE_9__*) ; 
 int /*<<< orphan*/  winmz_header_fields ; 
 int /*<<< orphan*/  winne_header_fields ; 
 int /*<<< orphan*/  winpe32_header_fields ; 
 int /*<<< orphan*/  winpe32_section_fields ; 
 int /*<<< orphan*/  winpe_rsrc_data_entry_fields ; 
 int /*<<< orphan*/  winpe_rsrc_dir_entry_fields ; 
 int /*<<< orphan*/  winpe_rsrc_dir_fields ; 

__attribute__((used)) static FT_Error
  fnt_face_get_dll_font( FNT_Face  face,
                         FT_Int    face_instance_index )
  {
    FT_Error         error;
    FT_Stream        stream = FT_FACE( face )->stream;
    FT_Memory        memory = FT_FACE( face )->memory;
    WinMZ_HeaderRec  mz_header;
    FT_Long          face_index;


    face->font = NULL;

    face_index = FT_ABS( face_instance_index ) & 0xFFFF;

    /* does it begin with an MZ header? */
    if ( FT_STREAM_SEEK( 0 )                                      ||
         FT_STREAM_READ_FIELDS( winmz_header_fields, &mz_header ) )
      goto Exit;

    error = FT_ERR( Unknown_File_Format );
    if ( mz_header.magic == WINFNT_MZ_MAGIC )
    {
      /* yes, now look for an NE header in the file */
      WinNE_HeaderRec  ne_header;


      FT_TRACE2(( "MZ signature found\n" ));

      if ( FT_STREAM_SEEK( mz_header.lfanew )                       ||
           FT_STREAM_READ_FIELDS( winne_header_fields, &ne_header ) )
        goto Exit;

      error = FT_ERR( Unknown_File_Format );
      if ( ne_header.magic == WINFNT_NE_MAGIC )
      {
        /* good, now look into the resource table for each FNT resource */
        FT_ULong   res_offset  = mz_header.lfanew +
                                   ne_header.resource_tab_offset;
        FT_UShort  size_shift;
        FT_UShort  font_count  = 0;
        FT_ULong   font_offset = 0;


        FT_TRACE2(( "NE signature found\n" ));

        if ( FT_STREAM_SEEK( res_offset )                    ||
             FT_FRAME_ENTER( ne_header.rname_tab_offset -
                             ne_header.resource_tab_offset ) )
          goto Exit;

        size_shift = FT_GET_USHORT_LE();

        /* Microsoft's specification of the executable-file header format */
        /* for `New Executable' (NE) doesn't give a limit for the         */
        /* alignment shift count; however, in 1985, the year of the       */
        /* specification release, only 32bit values were supported, thus  */
        /* anything larger than 16 doesn't make sense in general, given   */
        /* that file offsets are 16bit values, shifted by the alignment   */
        /* shift count                                                    */
        if ( size_shift > 16 )
        {
          FT_TRACE2(( "invalid alignment shift count for resource data\n" ));
          error = FT_THROW( Invalid_File_Format );
          goto Exit;
        }


        for (;;)
        {
          FT_UShort  type_id, count;


          type_id = FT_GET_USHORT_LE();
          if ( !type_id )
            break;

          count = FT_GET_USHORT_LE();

          if ( type_id == 0x8008U )
          {
            font_count  = count;
            font_offset = FT_STREAM_POS() + 4 +
                          (FT_ULong)( stream->cursor - stream->limit );
            break;
          }

          stream->cursor += 4 + count * 12;
        }

        FT_FRAME_EXIT();

        if ( !font_count || !font_offset )
        {
          FT_TRACE2(( "this file doesn't contain any FNT resources\n" ));
          error = FT_THROW( Invalid_File_Format );
          goto Exit;
        }

        /* loading `winfnt_header_fields' needs at least 118 bytes;    */
        /* use this as a rough measure to check the expected font size */
        if ( font_count * 118UL > stream->size )
        {
          FT_TRACE2(( "invalid number of faces\n" ));
          error = FT_THROW( Invalid_File_Format );
          goto Exit;
        }

        face->root.num_faces = font_count;

        if ( face_instance_index < 0 )
          goto Exit;

        if ( face_index >= font_count )
        {
          error = FT_THROW( Invalid_Argument );
          goto Exit;
        }

        if ( FT_NEW( face->font ) )
          goto Exit;

        if ( FT_STREAM_SEEK( font_offset + (FT_ULong)face_index * 12 ) ||
             FT_FRAME_ENTER( 12 )                                      )
          goto Fail;

        face->font->offset   = (FT_ULong)FT_GET_USHORT_LE() << size_shift;
        face->font->fnt_size = (FT_ULong)FT_GET_USHORT_LE() << size_shift;

        stream->cursor += 8;

        FT_FRAME_EXIT();

        error = fnt_font_load( face->font, stream );
      }
      else if ( ne_header.magic == WINFNT_PE_MAGIC )
      {
        WinPE32_HeaderRec       pe32_header;
        WinPE32_SectionRec      pe32_section;
        WinPE_RsrcDirRec        root_dir, name_dir, lang_dir;
        WinPE_RsrcDirEntryRec   dir_entry1, dir_entry2, dir_entry3;
        WinPE_RsrcDataEntryRec  data_entry;

        FT_ULong   root_dir_offset, name_dir_offset, lang_dir_offset;
        FT_UShort  i, j, k;


        FT_TRACE2(( "PE signature found\n" ));

        if ( FT_STREAM_SEEK( mz_header.lfanew )                           ||
             FT_STREAM_READ_FIELDS( winpe32_header_fields, &pe32_header ) )
          goto Exit;

        FT_TRACE2(( "magic %04lx, machine %02x, number_of_sections %u, "
                    "size_of_optional_header %02x\n"
                    "magic32 %02x, rsrc_virtual_address %04lx, "
                    "rsrc_size %04lx\n",
                    pe32_header.magic, pe32_header.machine,
                    pe32_header.number_of_sections,
                    pe32_header.size_of_optional_header,
                    pe32_header.magic32, pe32_header.rsrc_virtual_address,
                    pe32_header.rsrc_size ));

        if ( pe32_header.magic != WINFNT_PE_MAGIC /* check full signature */ ||
             pe32_header.machine != 0x014C /* i386 */                        ||
             pe32_header.size_of_optional_header != 0xE0 /* FIXME */         ||
             pe32_header.magic32 != 0x10B                                    )
        {
          FT_TRACE2(( "this file has an invalid PE header\n" ));
          error = FT_THROW( Invalid_File_Format );
          goto Exit;
        }

        face->root.num_faces = 0;

        for ( i = 0; i < pe32_header.number_of_sections; i++ )
        {
          if ( FT_STREAM_READ_FIELDS( winpe32_section_fields,
                                      &pe32_section ) )
            goto Exit;

          FT_TRACE2(( "name %.8s, va %04lx, size %04lx, offset %04lx\n",
                      pe32_section.name, pe32_section.virtual_address,
                      pe32_section.size_of_raw_data,
                      pe32_section.pointer_to_raw_data ));

          if ( pe32_header.rsrc_virtual_address ==
                 pe32_section.virtual_address )
            goto Found_rsrc_section;
        }

        FT_TRACE2(( "this file doesn't contain any resources\n" ));
        error = FT_THROW( Invalid_File_Format );
        goto Exit;

      Found_rsrc_section:
        FT_TRACE2(( "found resources section %.8s\n", pe32_section.name ));

        if ( FT_STREAM_SEEK( pe32_section.pointer_to_raw_data )        ||
             FT_STREAM_READ_FIELDS( winpe_rsrc_dir_fields, &root_dir ) )
          goto Exit;

        root_dir_offset = pe32_section.pointer_to_raw_data;

        for ( i = 0; i < root_dir.number_of_named_entries +
                           root_dir.number_of_id_entries; i++ )
        {
          if ( FT_STREAM_SEEK( root_dir_offset + 16 + i * 8 )      ||
               FT_STREAM_READ_FIELDS( winpe_rsrc_dir_entry_fields,
                                      &dir_entry1 )                )
            goto Exit;

          if ( !(dir_entry1.offset & 0x80000000UL ) /* DataIsDirectory */ )
          {
            error = FT_THROW( Invalid_File_Format );
            goto Exit;
          }

          dir_entry1.offset &= ~0x80000000UL;

          name_dir_offset = pe32_section.pointer_to_raw_data +
                            dir_entry1.offset;

          if ( FT_STREAM_SEEK( pe32_section.pointer_to_raw_data +
                               dir_entry1.offset )                       ||
               FT_STREAM_READ_FIELDS( winpe_rsrc_dir_fields, &name_dir ) )
            goto Exit;

          for ( j = 0; j < name_dir.number_of_named_entries +
                             name_dir.number_of_id_entries; j++ )
          {
            if ( FT_STREAM_SEEK( name_dir_offset + 16 + j * 8 )      ||
                 FT_STREAM_READ_FIELDS( winpe_rsrc_dir_entry_fields,
                                        &dir_entry2 )                )
              goto Exit;

            if ( !(dir_entry2.offset & 0x80000000UL ) /* DataIsDirectory */ )
            {
              error = FT_THROW( Invalid_File_Format );
              goto Exit;
            }

            dir_entry2.offset &= ~0x80000000UL;

            lang_dir_offset = pe32_section.pointer_to_raw_data +
                                dir_entry2.offset;

            if ( FT_STREAM_SEEK( pe32_section.pointer_to_raw_data +
                                   dir_entry2.offset )                     ||
                 FT_STREAM_READ_FIELDS( winpe_rsrc_dir_fields, &lang_dir ) )
              goto Exit;

            for ( k = 0; k < lang_dir.number_of_named_entries +
                               lang_dir.number_of_id_entries; k++ )
            {
              if ( FT_STREAM_SEEK( lang_dir_offset + 16 + k * 8 )      ||
                   FT_STREAM_READ_FIELDS( winpe_rsrc_dir_entry_fields,
                                          &dir_entry3 )                )
                goto Exit;

              if ( dir_entry2.offset & 0x80000000UL /* DataIsDirectory */ )
              {
                error = FT_THROW( Invalid_File_Format );
                goto Exit;
              }

              if ( dir_entry1.name == 8 /* RT_FONT */ )
              {
                if ( FT_STREAM_SEEK( root_dir_offset + dir_entry3.offset ) ||
                     FT_STREAM_READ_FIELDS( winpe_rsrc_data_entry_fields,
                                            &data_entry )                  )
                  goto Exit;

                FT_TRACE2(( "found font #%lu, offset %04lx, "
                            "size %04lx, cp %lu\n",
                            dir_entry2.name,
                            pe32_section.pointer_to_raw_data +
                              data_entry.offset_to_data -
                              pe32_section.virtual_address,
                            data_entry.size, data_entry.code_page ));

                if ( face_index == face->root.num_faces )
                {
                  if ( FT_NEW( face->font ) )
                    goto Exit;

                  face->font->offset   = pe32_section.pointer_to_raw_data +
                                           data_entry.offset_to_data -
                                           pe32_section.virtual_address;
                  face->font->fnt_size = data_entry.size;

                  error = fnt_font_load( face->font, stream );
                  if ( error )
                  {
                    FT_TRACE2(( "font #%lu load error 0x%x\n",
                                dir_entry2.name, error ));
                    goto Fail;
                  }
                  else
                    FT_TRACE2(( "font #%lu successfully loaded\n",
                                dir_entry2.name ));
                }

                face->root.num_faces++;
              }
            }
          }
        }
      }

      if ( !face->root.num_faces )
      {
        FT_TRACE2(( "this file doesn't contain any RT_FONT resources\n" ));
        error = FT_THROW( Invalid_File_Format );
        goto Exit;
      }

      if ( face_index >= face->root.num_faces )
      {
        error = FT_THROW( Invalid_Argument );
        goto Exit;
      }
    }

  Fail:
    if ( error )
      fnt_font_done( face );

  Exit:
    return error;
  }