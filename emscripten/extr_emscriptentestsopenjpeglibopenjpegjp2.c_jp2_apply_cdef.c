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
struct TYPE_7__ {TYPE_2__* jp2_cdef; } ;
typedef  TYPE_1__ opj_jp2_color_t ;
struct TYPE_8__ {unsigned short n; unsigned short asoc; unsigned short cn; unsigned short typ; struct TYPE_8__* info; } ;
typedef  TYPE_2__ opj_jp2_cdef_info_t ;
struct TYPE_9__ {int color_space; int /*<<< orphan*/ * comps; } ;
typedef  TYPE_3__ opj_image_t ;
typedef  int /*<<< orphan*/  opj_image_comp_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  opj_free (TYPE_2__*) ; 

__attribute__((used)) static void jp2_apply_cdef(opj_image_t *image, opj_jp2_color_t *color)
{
	opj_jp2_cdef_info_t *info;
	int color_space;
	unsigned short i, n, cn, typ, asoc, acn;

	color_space = image->color_space;
	info = color->jp2_cdef->info;
	n = color->jp2_cdef->n;

	for(i = 0; i < n; ++i)
   {
/* WATCH: acn = asoc - 1 ! */
	if((asoc = info[i].asoc) == 0) continue;

	cn = info[i].cn; typ = info[i].typ; acn = asoc - 1;

	if(cn != acn)
  {
	opj_image_comp_t saved;

	memcpy(&saved, &image->comps[cn], sizeof(opj_image_comp_t));
	memcpy(&image->comps[cn], &image->comps[acn], sizeof(opj_image_comp_t));
	memcpy(&image->comps[acn], &saved, sizeof(opj_image_comp_t));

	info[i].asoc = cn + 1;
	info[acn].asoc = info[acn].cn + 1;
  }
   }
	if(color->jp2_cdef->info) opj_free(color->jp2_cdef->info);

	opj_free(color->jp2_cdef); color->jp2_cdef = NULL;

}