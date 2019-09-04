#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int numcomps; int /*<<< orphan*/  color_space; TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_7__ {int dx; int dy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLRSPC_GRAY ; 
 int /*<<< orphan*/  CLRSPC_SRGB ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sycc420_to_rgb (TYPE_2__*) ; 
 int /*<<< orphan*/  sycc422_to_rgb (TYPE_2__*) ; 
 int /*<<< orphan*/  sycc444_to_rgb (TYPE_2__*) ; 

void color_sycc_to_rgb(opj_image_t *img)
{
	if(img->numcomps < 3) 
   {
	img->color_space = CLRSPC_GRAY;
	return;
   }

	if((img->comps[0].dx == 1)
	&& (img->comps[1].dx == 2)
	&& (img->comps[2].dx == 2)
	&& (img->comps[0].dy == 1)
	&& (img->comps[1].dy == 2)
	&& (img->comps[2].dy == 2))/* horizontal and vertical sub-sample */
  {
	sycc420_to_rgb(img);
  }
	else
	if((img->comps[0].dx == 1)
	&& (img->comps[1].dx == 2)
	&& (img->comps[2].dx == 2)
	&& (img->comps[0].dy == 1)
	&& (img->comps[1].dy == 1)
	&& (img->comps[2].dy == 1))/* horizontal sub-sample only */
  {
	sycc422_to_rgb(img);
  }
	else
	if((img->comps[0].dx == 1)
	&& (img->comps[1].dx == 1)
	&& (img->comps[2].dx == 1)
	&& (img->comps[0].dy == 1)
	&& (img->comps[1].dy == 1)
	&& (img->comps[2].dy == 1))/* no sub-sample */
  {
	sycc444_to_rgb(img);
  }
	else
  {
	fprintf(stderr,"%s:%d:color_sycc_to_rgb\n\tCAN NOT CONVERT\n",
	 __FILE__,__LINE__);
	return;
  }
	img->color_space = CLRSPC_SRGB;

}