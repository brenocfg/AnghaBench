#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* s; } ;
typedef  TYPE_1__ stbi__png ;
struct TYPE_6__ {int img_x; int img_y; int img_n; } ;

/* Variables and functions */
 int /*<<< orphan*/  STBI__SCAN_header ; 
 int /*<<< orphan*/  stbi__parse_png_file (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbi__rewind (TYPE_2__*) ; 

__attribute__((used)) static int stbi__png_info_raw(stbi__png *p, int *x, int *y, int *comp)
{
   if (!stbi__parse_png_file(p, STBI__SCAN_header, 0)) {
      stbi__rewind( p->s );
      return 0;
   }
   if (x) *x = p->s->img_x;
   if (y) *y = p->s->img_y;
   if (comp) *comp = p->s->img_n;
   return 1;
}