#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* max_bin_blocks; void* bin_block_size; void* force_dither_off; void* clif_dump_on_lock; void* reg_dump_on_lock; void* no_bin_render_overlap; void* double_buffer; void* gl_error_assist; } ;
typedef  int /*<<< orphan*/  KHRN_OPTIONS_T ;

/* Variables and functions */
 TYPE_1__ khrn_options ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* read_bool_option (char*,void*) ; 
 void* read_uint32_option (char*,void*) ; 

void khrn_init_options(void)
{
   /* Default values are all 0 */
   memset(&khrn_options, 0, sizeof(KHRN_OPTIONS_T));

#ifndef DISABLE_OPTION_PARSING
   /* Now read the options */
   khrn_options.gl_error_assist        = read_bool_option(  "V3D_GL_ERROR_ASSIST",        khrn_options.gl_error_assist);
   khrn_options.double_buffer          = read_bool_option(  "V3D_DOUBLE_BUFFER",          khrn_options.double_buffer);
   khrn_options.no_bin_render_overlap  = read_bool_option(  "V3D_NO_BIN_RENDER_OVERLAP",  khrn_options.no_bin_render_overlap);
   khrn_options.reg_dump_on_lock       = read_bool_option(  "V3D_REG_DUMP_ON_LOCK",       khrn_options.reg_dump_on_lock);
   khrn_options.clif_dump_on_lock      = read_bool_option(  "V3D_CLIF_DUMP_ON_LOCK",      khrn_options.clif_dump_on_lock);
   khrn_options.force_dither_off       = read_bool_option(  "V3D_FORCE_DITHER_OFF",       khrn_options.force_dither_off);

   khrn_options.bin_block_size         = read_uint32_option("V3D_BIN_BLOCK_SIZE",         khrn_options.bin_block_size);
   khrn_options.max_bin_blocks         = read_uint32_option("V3D_MAX_BIN_BLOCKS",         khrn_options.max_bin_blocks);
#endif
}