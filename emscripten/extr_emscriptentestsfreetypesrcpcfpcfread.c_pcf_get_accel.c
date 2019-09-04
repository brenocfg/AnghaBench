#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  maxbounds; int /*<<< orphan*/  ink_maxbounds; int /*<<< orphan*/  minbounds; int /*<<< orphan*/  ink_minbounds; } ;
struct TYPE_6__ {int /*<<< orphan*/  count; int /*<<< orphan*/  tables; } ;
struct TYPE_7__ {TYPE_1__ toc; TYPE_3__ accel; } ;
typedef  TYPE_2__* PCF_Face ;
typedef  TYPE_3__* PCF_Accel ;
typedef  int FT_ULong ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ FT_READ_ULONG_LE (int) ; 
 scalar_t__ FT_STREAM_READ_FIELDS (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ MSBFirst ; 
 int /*<<< orphan*/  PCF_ACCEL_W_INKBOUNDS ; 
 scalar_t__ PCF_BYTE_ORDER (int) ; 
 int /*<<< orphan*/  PCF_DEFAULT_FORMAT ; 
 scalar_t__ PCF_Err_Ok ; 
 int PCF_FORMAT_MASK ; 
 scalar_t__ PCF_FORMAT_MATCH (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf_accel_header ; 
 int /*<<< orphan*/  pcf_accel_msb_header ; 
 scalar_t__ pcf_get_metric (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ pcf_seek_to_table_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 

__attribute__((used)) static FT_Error
  pcf_get_accel( FT_Stream  stream,
                 PCF_Face   face,
                 FT_ULong   type )
  {
    FT_ULong   format, size;
    FT_Error   error = PCF_Err_Ok;
    PCF_Accel  accel = &face->accel;


    error = pcf_seek_to_table_type( stream,
                                    face->toc.tables,
                                    face->toc.count,
                                    type,
                                    &format,
                                    &size );
    if ( error )
      goto Bail;

    if ( FT_READ_ULONG_LE( format ) )
      goto Bail;

    if ( !PCF_FORMAT_MATCH( format, PCF_DEFAULT_FORMAT )    &&
         !PCF_FORMAT_MATCH( format, PCF_ACCEL_W_INKBOUNDS ) )
      goto Bail;

    if ( PCF_BYTE_ORDER( format ) == MSBFirst )
    {
      if ( FT_STREAM_READ_FIELDS( pcf_accel_msb_header, accel ) )
        goto Bail;
    }
    else
    {
      if ( FT_STREAM_READ_FIELDS( pcf_accel_header, accel ) )
        goto Bail;
    }

    error = pcf_get_metric( stream,
                            format & ( ~PCF_FORMAT_MASK ),
                            &(accel->minbounds) );
    if ( error )
      goto Bail;

    error = pcf_get_metric( stream,
                            format & ( ~PCF_FORMAT_MASK ),
                            &(accel->maxbounds) );
    if ( error )
      goto Bail;

    if ( PCF_FORMAT_MATCH( format, PCF_ACCEL_W_INKBOUNDS ) )
    {
      error = pcf_get_metric( stream,
                              format & ( ~PCF_FORMAT_MASK ),
                              &(accel->ink_minbounds) );
      if ( error )
        goto Bail;

      error = pcf_get_metric( stream,
                              format & ( ~PCF_FORMAT_MASK ),
                              &(accel->ink_maxbounds) );
      if ( error )
        goto Bail;
    }
    else
    {
      accel->ink_minbounds = accel->minbounds; /* I'm not sure about this */
      accel->ink_maxbounds = accel->maxbounds;
    }

  Bail:
    return error;
  }