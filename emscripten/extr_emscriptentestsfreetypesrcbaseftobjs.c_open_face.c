#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  memory; } ;
struct TYPE_18__ {TYPE_1__ root; TYPE_4__* clazz; } ;
struct TYPE_17__ {scalar_t__ (* init_face ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* done_face ) (TYPE_2__*) ;int /*<<< orphan*/  face_object_size; } ;
struct TYPE_16__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  memory; TYPE_5__* driver; struct TYPE_16__* internal; } ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  int /*<<< orphan*/  FT_Parameter ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Long ;
typedef  int /*<<< orphan*/  FT_Int ;
typedef  TYPE_2__* FT_Face_Internal ;
typedef  TYPE_2__* FT_Face ;
typedef  scalar_t__ FT_Error ;
typedef  TYPE_4__* FT_Driver_Class ;
typedef  TYPE_5__* FT_Driver ;

/* Variables and functions */
 scalar_t__ FT_ALLOC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_Err_Invalid_CharMap_Handle ; 
 int /*<<< orphan*/  FT_FREE (TYPE_2__*) ; 
 scalar_t__ FT_NEW (TYPE_2__*) ; 
 int /*<<< orphan*/  destroy_charmaps (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_unicode_charmap (TYPE_2__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 

__attribute__((used)) static FT_Error
  open_face( FT_Driver      driver,
             FT_Stream      stream,
             FT_Long        face_index,
             FT_Int         num_params,
             FT_Parameter*  params,
             FT_Face       *aface )
  {
    FT_Memory         memory;
    FT_Driver_Class   clazz;
    FT_Face           face = 0;
    FT_Error          error, error2;
    FT_Face_Internal  internal = NULL;


    clazz  = driver->clazz;
    memory = driver->root.memory;

    /* allocate the face object and perform basic initialization */
    if ( FT_ALLOC( face, clazz->face_object_size ) )
      goto Fail;

    if ( FT_NEW( internal ) )
      goto Fail;

    face->internal = internal;

    face->driver   = driver;
    face->memory   = memory;
    face->stream   = stream;

#ifdef FT_CONFIG_OPTION_INCREMENTAL
    {
      int  i;


      face->internal->incremental_interface = 0;
      for ( i = 0; i < num_params && !face->internal->incremental_interface;
            i++ )
        if ( params[i].tag == FT_PARAM_TAG_INCREMENTAL )
          face->internal->incremental_interface =
            (FT_Incremental_Interface)params[i].data;
    }
#endif

    if ( clazz->init_face )
      error = clazz->init_face( stream,
                                face,
                                (FT_Int)face_index,
                                num_params,
                                params );
    if ( error )
      goto Fail;

    /* select Unicode charmap by default */
    error2 = find_unicode_charmap( face );

    /* if no Unicode charmap can be found, FT_Err_Invalid_CharMap_Handle */
    /* is returned.                                                      */

    /* no error should happen, but we want to play safe */
    if ( error2 && error2 != FT_Err_Invalid_CharMap_Handle )
    {
      error = error2;
      goto Fail;
    }

    *aface = face;

  Fail:
    if ( error )
    {
      destroy_charmaps( face, memory );
      if ( clazz->done_face )
        clazz->done_face( face );
      FT_FREE( internal );
      FT_FREE( face );
      *aface = 0;
    }

    return error;
  }