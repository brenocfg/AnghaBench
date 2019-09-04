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
struct f_fi {scalar_t__ r; int e; int i; int /*<<< orphan*/  x; int /*<<< orphan*/  dy; int /*<<< orphan*/  y; } ;

/* Variables and functions */
 int DIVBYZERO ; 
 int /*<<< orphan*/  checkulp (float,scalar_t__) ; 
 int /*<<< orphan*/  inf ; 
 int /*<<< orphan*/  isnan (int /*<<< orphan*/ ) ; 
 double lgammaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,double,int) ; 
 int signgam ; 
 struct f_fi* t ; 
 float ulperrf (double,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(void)
{
	int yi;
	double y;
	float d;
	int e, i, err = 0;
	struct f_fi *p;

	for (i = 0; i < sizeof t/sizeof *t; i++) {
		p = t + i;

		if (p->r < 0)
			continue;
		y = lgammaf(p->x);
		yi = signgam;

    printf("%g,%d\n", y, yi);

		d = ulperrf(y, p->y, p->dy);
		if (!checkulp(d, p->r) || (!isnan(p->x) && p->x!=-inf && !(p->e&DIVBYZERO) && yi != p->i)) {
      /* printf("%s:%d: %d lgammaf(%g) want %g,%lld got %g,%d ulperr %.3f = %g + %g\n",
				p->file, p->line, p->r, p->x, p->y, p->i, y, yi, d, d-p->dy, p->dy); */
			err++;
		}
	}
	return !!err;
}