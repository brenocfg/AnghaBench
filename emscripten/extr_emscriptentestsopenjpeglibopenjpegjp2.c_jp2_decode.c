#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int enumcs; int /*<<< orphan*/  j2k; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_2__ opj_jp2_t ;
struct TYPE_19__ {int /*<<< orphan*/  icc_profile_len; int /*<<< orphan*/ * icc_profile_buf; TYPE_1__* jp2_pclr; scalar_t__ jp2_cdef; } ;
typedef  TYPE_3__ opj_jp2_color_t ;
struct TYPE_20__ {int /*<<< orphan*/  icc_profile_len; int /*<<< orphan*/ * icc_profile_buf; int /*<<< orphan*/  color_space; } ;
typedef  TYPE_4__ opj_image_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_codestream_info_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_17__ {int /*<<< orphan*/  cmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLRSPC_GRAY ; 
 int /*<<< orphan*/  CLRSPC_SRGB ; 
 int /*<<< orphan*/  CLRSPC_SYCC ; 
 int /*<<< orphan*/  CLRSPC_UNKNOWN ; 
 int /*<<< orphan*/  EVT_ERROR ; 
 int /*<<< orphan*/  free_color_data (TYPE_3__*) ; 
 TYPE_4__* j2k_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jp2_apply_cdef (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  jp2_apply_pclr (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  jp2_free_pclr (TYPE_3__*) ; 
 int /*<<< orphan*/  jp2_read_struct (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

opj_image_t* jp2_decode(opj_jp2_t *jp2, opj_cio_t *cio, 
	opj_codestream_info_t *cstr_info) 
{
	opj_common_ptr cinfo;
	opj_image_t *image = NULL;
	opj_jp2_color_t color;

	if(!jp2 || !cio) 
   {
	return NULL;
   }
	memset(&color, 0, sizeof(opj_jp2_color_t));
	cinfo = jp2->cinfo;

/* JP2 decoding */
	if(!jp2_read_struct(jp2, cio, &color)) 
   {
	free_color_data(&color);
	opj_event_msg(cinfo, EVT_ERROR, "Failed to decode jp2 structure\n");
	return NULL;
   }

/* J2K decoding */
	image = j2k_decode(jp2->j2k, cio, cstr_info);

	if(!image) 
   {
	free_color_data(&color);
	opj_event_msg(cinfo, EVT_ERROR, "Failed to decode J2K image\n");
	return NULL;
   }

/* Set Image Color Space */
	if (jp2->enumcs == 16)
		image->color_space = CLRSPC_SRGB;
	else if (jp2->enumcs == 17)
		image->color_space = CLRSPC_GRAY;
	else if (jp2->enumcs == 18)
		image->color_space = CLRSPC_SYCC;
	else
		image->color_space = CLRSPC_UNKNOWN;

	if(color.jp2_cdef)
   {
	jp2_apply_cdef(image, &color);
   }
	if(color.jp2_pclr)
   {
/* Part 1, I.5.3.4: Either both or none : */
	if( !color.jp2_pclr->cmap) 
	 jp2_free_pclr(&color);
	else
	 jp2_apply_pclr(&color, image);
   }
	if(color.icc_profile_buf)
   {
	image->icc_profile_buf = color.icc_profile_buf;
	color.icc_profile_buf = NULL;
	image->icc_profile_len = color.icc_profile_len;
   }
	return image;

}