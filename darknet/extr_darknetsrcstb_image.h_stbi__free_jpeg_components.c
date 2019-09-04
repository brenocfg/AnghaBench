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
struct TYPE_5__ {TYPE_1__* img_comp; } ;
typedef  TYPE_2__ stbi__jpeg ;
struct TYPE_4__ {int /*<<< orphan*/ * linebuf; scalar_t__ coeff; int /*<<< orphan*/ * raw_coeff; int /*<<< orphan*/ * data; int /*<<< orphan*/ * raw_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  STBI_FREE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stbi__free_jpeg_components(stbi__jpeg *z, int ncomp, int why)
{
   int i;
   for (i=0; i < ncomp; ++i) {
      if (z->img_comp[i].raw_data) {
         STBI_FREE(z->img_comp[i].raw_data);
         z->img_comp[i].raw_data = NULL;
         z->img_comp[i].data = NULL;
      }
      if (z->img_comp[i].raw_coeff) {
         STBI_FREE(z->img_comp[i].raw_coeff);
         z->img_comp[i].raw_coeff = 0;
         z->img_comp[i].coeff = 0;
      }
      if (z->img_comp[i].linebuf) {
         STBI_FREE(z->img_comp[i].linebuf);
         z->img_comp[i].linebuf = NULL;
      }
   }
   return why;
}