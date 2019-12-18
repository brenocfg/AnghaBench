#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  color; } ;
typedef  TYPE_1__ LodePNGInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CERROR_TRY_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LodePNGIText_copy (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  LodePNGText_copy (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  LodePNGUnknownChunks_copy (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  LodePNGUnknownChunks_init (TYPE_1__*) ; 
 int /*<<< orphan*/  lodepng_color_mode_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lodepng_color_mode_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lodepng_info_cleanup (TYPE_1__*) ; 

unsigned lodepng_info_copy(LodePNGInfo* dest, const LodePNGInfo* source)
{
  lodepng_info_cleanup(dest);
  *dest = *source;
  lodepng_color_mode_init(&dest->color);
  CERROR_TRY_RETURN(lodepng_color_mode_copy(&dest->color, &source->color));

#ifdef LODEPNG_COMPILE_ANCILLARY_CHUNKS
  CERROR_TRY_RETURN(LodePNGText_copy(dest, source));
  CERROR_TRY_RETURN(LodePNGIText_copy(dest, source));

  LodePNGUnknownChunks_init(dest);
  CERROR_TRY_RETURN(LodePNGUnknownChunks_copy(dest, source));
#endif /*LODEPNG_COMPILE_ANCILLARY_CHUNKS*/
  return 0;
}