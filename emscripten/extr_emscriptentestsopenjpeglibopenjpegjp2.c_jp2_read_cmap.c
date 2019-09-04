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
struct TYPE_6__ {TYPE_1__* jp2_pclr; } ;
typedef  TYPE_2__ opj_jp2_color_t ;
struct TYPE_7__ {void* pcol; void* mtyp; void* cmp; } ;
typedef  TYPE_3__ opj_jp2_cmap_comp_t ;
typedef  int /*<<< orphan*/  opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;
struct TYPE_5__ {unsigned short nr_channels; TYPE_3__* cmap; } ;

/* Variables and functions */
 void* cio_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ opj_malloc (unsigned short) ; 

__attribute__((used)) static bool jp2_read_cmap(opj_jp2_t *jp2, opj_cio_t *cio,
	opj_jp2_box_t *box, opj_jp2_color_t *color)
{
	opj_jp2_cmap_comp_t *cmap;
	unsigned short i, nr_channels;

/* Need nr_channels: */
	if(color->jp2_pclr == NULL) return false;

/* Part 1, I.5.3.5: 'There shall be at most one Component Mapping box
 * inside a JP2 Header box' :
*/
	if(color->jp2_pclr->cmap) return false;

	nr_channels = color->jp2_pclr->nr_channels;
	cmap = (opj_jp2_cmap_comp_t*)
	 opj_malloc(nr_channels * sizeof(opj_jp2_cmap_comp_t));

	for(i = 0; i < nr_channels; ++i)
   {
	cmap[i].cmp = cio_read(cio, 2);
	cmap[i].mtyp = cio_read(cio, 1);
	cmap[i].pcol = cio_read(cio, 1);

   }
	color->jp2_pclr->cmap = cmap;

	return true;
}