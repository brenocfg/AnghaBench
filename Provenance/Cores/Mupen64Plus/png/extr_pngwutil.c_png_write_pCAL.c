#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  int /*<<< orphan*/  png_structrp ;
typedef  scalar_t__* png_size_tp ;
typedef  scalar_t__ png_size_t ;
typedef  int /*<<< orphan*/  png_int_32 ;
typedef  scalar_t__ png_const_charp ;
typedef  scalar_t__* png_const_bytep ;
typedef  scalar_t__* png_charpp ;
typedef  int /*<<< orphan*/  png_charp ;
typedef  scalar_t__ png_byte ;
typedef  int png_alloc_size_t ;

/* Variables and functions */
 int PNG_EQUATION_LAST ; 
 scalar_t__ png_check_keyword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  png_debug1 (int,char*,int) ; 
 int /*<<< orphan*/  png_debug2 (int,char*,int,unsigned long) ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  png_free (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ png_malloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  png_pCAL ; 
 int /*<<< orphan*/  png_save_int_32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_chunk_data (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  png_write_chunk_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_chunk_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (scalar_t__) ; 

void /* PRIVATE */
png_write_pCAL(png_structrp png_ptr, png_charp purpose, png_int_32 X0,
    png_int_32 X1, int type, int nparams, png_const_charp units,
    png_charpp params)
{
   png_uint_32 purpose_len;
   png_size_t units_len, total_len;
   png_size_tp params_len;
   png_byte buf[10];
   png_byte new_purpose[80];
   int i;

   png_debug1(1, "in png_write_pCAL (%d parameters)", nparams);

   if (type >= PNG_EQUATION_LAST)
      png_error(png_ptr, "Unrecognized equation type for pCAL chunk");

   purpose_len = png_check_keyword(png_ptr, purpose, new_purpose);

   if (purpose_len == 0)
      png_error(png_ptr, "pCAL: invalid keyword");

   ++purpose_len; /* terminator */

   png_debug1(3, "pCAL purpose length = %d", (int)purpose_len);
   units_len = strlen(units) + (nparams == 0 ? 0 : 1);
   png_debug1(3, "pCAL units length = %d", (int)units_len);
   total_len = purpose_len + units_len + 10;

   params_len = (png_size_tp)png_malloc(png_ptr,
       (png_alloc_size_t)((png_alloc_size_t)nparams * (sizeof (png_size_t))));

   /* Find the length of each parameter, making sure we don't count the
    * null terminator for the last parameter.
    */
   for (i = 0; i < nparams; i++)
   {
      params_len[i] = strlen(params[i]) + (i == nparams - 1 ? 0 : 1);
      png_debug2(3, "pCAL parameter %d length = %lu", i,
          (unsigned long)params_len[i]);
      total_len += params_len[i];
   }

   png_debug1(3, "pCAL total length = %d", (int)total_len);
   png_write_chunk_header(png_ptr, png_pCAL, (png_uint_32)total_len);
   png_write_chunk_data(png_ptr, new_purpose, purpose_len);
   png_save_int_32(buf, X0);
   png_save_int_32(buf + 4, X1);
   buf[8] = (png_byte)type;
   buf[9] = (png_byte)nparams;
   png_write_chunk_data(png_ptr, buf, (png_size_t)10);
   png_write_chunk_data(png_ptr, (png_const_bytep)units, (png_size_t)units_len);

   for (i = 0; i < nparams; i++)
   {
      png_write_chunk_data(png_ptr, (png_const_bytep)params[i], params_len[i]);
   }

   png_free(png_ptr, params_len);
   png_write_chunk_end(png_ptr);
}