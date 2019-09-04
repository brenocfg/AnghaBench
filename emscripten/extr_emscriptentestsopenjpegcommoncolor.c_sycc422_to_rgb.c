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
struct TYPE_5__ {TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_4__ {int prec; int w; int h; int* data; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sycc_to_rgb (int,int,int const,int const,int const,int*,int*,int*) ; 

__attribute__((used)) static void sycc422_to_rgb(opj_image_t *img)
{	
	int *d0, *d1, *d2, *r, *g, *b;
	const int *y, *cb, *cr;
	int maxw, maxh, max, offset, upb;
	int i, j;

	i = img->comps[0].prec;
	offset = 1<<(i - 1); upb = (1<<i)-1;

	maxw = img->comps[0].w; maxh = img->comps[0].h;
	max = maxw * maxh;

	y = img->comps[0].data;
	cb = img->comps[1].data;
	cr = img->comps[2].data;

	d0 = r = (int*)malloc(sizeof(int) * max);
	d1 = g = (int*)malloc(sizeof(int) * max);
	d2 = b = (int*)malloc(sizeof(int) * max);

	for(i=0; i < maxh; ++i)
   {
	for(j=0; j < maxw; j += 2)
  {
	sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);

	++y; ++r; ++g; ++b;

	sycc_to_rgb(offset, upb, *y, *cb, *cr, r, g, b);

	++y; ++r; ++g; ++b; ++cb; ++cr;
  }
   }
	free(img->comps[0].data); img->comps[0].data = d0;
	free(img->comps[1].data); img->comps[1].data = d1;
	free(img->comps[2].data); img->comps[2].data = d2;

	img->comps[1].w = maxw; img->comps[1].h = maxh;
	img->comps[2].w = maxw; img->comps[2].h = maxh;
	img->comps[1].dx = img->comps[0].dx;
	img->comps[2].dx = img->comps[0].dx;
	img->comps[1].dy = img->comps[0].dy;
	img->comps[2].dy = img->comps[0].dy;

}