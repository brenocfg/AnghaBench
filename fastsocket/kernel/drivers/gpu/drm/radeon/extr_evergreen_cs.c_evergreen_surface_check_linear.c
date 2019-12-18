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
struct radeon_cs_parser {int dummy; } ;
struct eg_surface {int layer_size; int nbx; int nby; int bpe; int nsamples; int base_align; int palign; int halign; } ;

/* Variables and functions */

__attribute__((used)) static int evergreen_surface_check_linear(struct radeon_cs_parser *p,
					  struct eg_surface *surf,
					  const char *prefix)
{
	surf->layer_size = surf->nbx * surf->nby * surf->bpe * surf->nsamples;
	surf->base_align = surf->bpe;
	surf->palign = 1;
	surf->halign = 1;
	return 0;
}