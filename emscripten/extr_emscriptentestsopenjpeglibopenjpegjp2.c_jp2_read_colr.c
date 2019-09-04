#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int meth; void* enumcs; void* approx; void* precedence; int /*<<< orphan*/  cinfo; } ;
typedef  TYPE_1__ opj_jp2_t ;
struct TYPE_8__ {int jp2_has_colr; unsigned char* icc_profile_buf; int icc_profile_len; } ;
typedef  TYPE_2__ opj_jp2_color_t ;
struct TYPE_9__ {scalar_t__ init_pos; scalar_t__ length; } ;
typedef  TYPE_3__ opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_common_ptr ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_ERROR ; 
 unsigned char* cio_getbp (int /*<<< orphan*/ *) ; 
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_skip (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ cio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  opj_event_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ opj_malloc (int) ; 

__attribute__((used)) static bool jp2_read_colr(opj_jp2_t *jp2, opj_cio_t *cio,
	opj_jp2_box_t *box, opj_jp2_color_t *color) 
{
	int skip_len;
    opj_common_ptr cinfo;

/* Part 1, I.5.3.3 : 'A conforming JP2 reader shall ignore all Colour
 * Specification boxes after the first.' 
*/
	if(color->jp2_has_colr) return false;

	cinfo = jp2->cinfo;

	jp2->meth = cio_read(cio, 1);		/* METH */
	jp2->precedence = cio_read(cio, 1);	/* PRECEDENCE */
	jp2->approx = cio_read(cio, 1);		/* APPROX */

	if (jp2->meth == 1) 
   {
	jp2->enumcs = cio_read(cio, 4);	/* EnumCS */
   } 
	else 
   {
/* skip PROFILE */
	skip_len = box->init_pos + box->length - cio_tell(cio);
	if (skip_len < 0) 
  {
	opj_event_msg(cinfo, EVT_ERROR, "Error with COLR box size\n");
	return false;
  }
	if(skip_len > 0)
  {
	unsigned char *start;

	start = cio_getbp(cio);
	color->icc_profile_buf = (unsigned char*)opj_malloc(skip_len);
	color->icc_profile_len = skip_len;

	cio_skip(cio, box->init_pos + box->length - cio_tell(cio));

	memcpy(color->icc_profile_buf, start, skip_len);
  }
   }

	if (cio_tell(cio) - box->init_pos != box->length) 
   {
	opj_event_msg(cinfo, EVT_ERROR, "Error with COLR Box\n");
	return false;
   }
	color->jp2_has_colr = 1;

	return true;
}