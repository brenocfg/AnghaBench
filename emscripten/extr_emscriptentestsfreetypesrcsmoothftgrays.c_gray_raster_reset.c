#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* buffer; long buffer_size; int band_size; int /*<<< orphan*/ * worker; } ;
typedef  int /*<<< orphan*/  TWorker ;
typedef  int /*<<< orphan*/  TCell ;
typedef  int /*<<< orphan*/ * PWorker ;
typedef  TYPE_1__* PRaster ;
typedef  scalar_t__ FT_Raster ;

/* Variables and functions */

__attribute__((used)) static void
  gray_raster_reset( FT_Raster  raster,
                     char*      pool_base,
                     long       pool_size )
  {
    PRaster  rast = (PRaster)raster;


    if ( raster )
    {
      if ( pool_base && pool_size >= (long)sizeof ( TWorker ) + 2048 )
      {
        PWorker  worker = (PWorker)pool_base;


        rast->worker      = worker;
        rast->buffer      = pool_base +
                              ( ( sizeof ( TWorker ) + sizeof ( TCell ) - 1 ) &
                                ~( sizeof ( TCell ) - 1 ) );
        rast->buffer_size = (long)( ( pool_base + pool_size ) -
                                    (char*)rast->buffer ) &
                                      ~( sizeof ( TCell ) - 1 );
        rast->band_size   = (int)( rast->buffer_size /
                                     ( sizeof ( TCell ) * 8 ) );
      }
      else
      {
        rast->buffer      = NULL;
        rast->buffer_size = 0;
        rast->worker      = NULL;
      }
    }
  }