#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opj_jp2_t ;
struct TYPE_4__ {unsigned char* channel_sign; unsigned char* channel_size; unsigned int* entries; unsigned short nr_entries; unsigned short nr_channels; int /*<<< orphan*/ * cmap; } ;
typedef  TYPE_1__ opj_jp2_pclr_t ;
struct TYPE_5__ {TYPE_1__* jp2_pclr; } ;
typedef  TYPE_2__ opj_jp2_color_t ;
typedef  int /*<<< orphan*/  opj_jp2_box_t ;
typedef  int /*<<< orphan*/  opj_cio_t ;

/* Variables and functions */
 void* cio_read (int /*<<< orphan*/ *,unsigned char) ; 
 scalar_t__ opj_malloc (int) ; 

__attribute__((used)) static bool jp2_read_pclr(opj_jp2_t *jp2, opj_cio_t *cio,
	opj_jp2_box_t *box, opj_jp2_color_t *color)
{
	opj_jp2_pclr_t *jp2_pclr;
	unsigned char *channel_size, *channel_sign;
	unsigned int *entries;
	unsigned short nr_entries, nr_channels;
	unsigned short i, j;
	unsigned char uc;

/* Part 1, I.5.3.4: 'There shall be at most one Palette box inside
 * a JP2 Header box' :
*/
	if(color->jp2_pclr) return false;

	nr_entries = cio_read(cio, 2); /* NE */
	nr_channels = cio_read(cio, 1);/* NPC */

	entries = (unsigned int*)
	 opj_malloc(nr_channels * nr_entries * sizeof(unsigned int));
	channel_size = (unsigned char*)opj_malloc(nr_channels);
	channel_sign = (unsigned char*)opj_malloc(nr_channels);

	jp2_pclr = (opj_jp2_pclr_t*)opj_malloc(sizeof(opj_jp2_pclr_t));
	jp2_pclr->channel_sign = channel_sign;
	jp2_pclr->channel_size = channel_size;
	jp2_pclr->entries = entries;
	jp2_pclr->nr_entries = nr_entries;
	jp2_pclr->nr_channels = nr_channels;
	jp2_pclr->cmap = NULL;

	color->jp2_pclr = jp2_pclr;

	for(i = 0; i < nr_channels; ++i)
   {
	uc = cio_read(cio, 1); /* Bi */
	channel_size[i] = (uc & 0x7f) + 1;
	channel_sign[i] = (uc & 0x80)?1:0;
   }

	for(j = 0; j < nr_entries; ++j)
   {
	for(i = 0; i < nr_channels; ++i)
  {
/* Cji */
	*entries++ = cio_read(cio, channel_size[i]>>3);
  }
   }

	return true;
}