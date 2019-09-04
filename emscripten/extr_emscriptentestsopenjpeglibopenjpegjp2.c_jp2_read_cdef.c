#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_jp2_t ;
struct TYPE_5__ {TYPE_2__* jp2_cdef; } ;
typedef  TYPE_1__ opj_jp2_color_t ;
struct TYPE_6__ {unsigned short n; TYPE_3__* info; } ;
typedef  TYPE_2__ opj_jp2_cdef_t ;
struct TYPE_7__ {void* asoc; void* typ; void* cn; } ;
typedef  TYPE_3__ opj_jp2_cdef_info_t ;
typedef  int /*<<< orphan*/  opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ opj_malloc (int) ; 

__attribute__((used)) static bool jp2_read_cdef(opj_jp2_t *jp2, opj_cio_t *cio,
	opj_jp2_box_t *box, opj_jp2_color_t *color)
{
	opj_jp2_cdef_info_t *info;
	unsigned short i, n;

/* Part 1, I.5.3.6: 'The shall be at most one Channel Definition box
 * inside a JP2 Header box.' 
*/
	if(color->jp2_cdef) return false;

	if((n = cio_read(cio, 2)) == 0) return false; /* szukw000: FIXME */

	info = (opj_jp2_cdef_info_t*)
	 opj_malloc(n * sizeof(opj_jp2_cdef_info_t));

	color->jp2_cdef = (opj_jp2_cdef_t*)opj_malloc(sizeof(opj_jp2_cdef_t));
	color->jp2_cdef->info = info;
	color->jp2_cdef->n = n;

	for(i = 0; i < n; ++i)
   {
	info[i].cn = cio_read(cio, 2);
	info[i].typ = cio_read(cio, 2);
	info[i].asoc = cio_read(cio, 2);

   }
	return true;
}