#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mode; scalar_t__ locale; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 scalar_t__ C_LOCALE ; 
 int /*<<< orphan*/  FLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_1__*) ; 
 int MB_CUR_MAX ; 
 scalar_t__ UTF8_LOCALE ; 

int fwide(FILE *f, int mode)
{
	FLOCK(f);
	if (mode) {
		if (!f->locale) f->locale = MB_CUR_MAX==1
			? C_LOCALE : UTF8_LOCALE;
		if (!f->mode) f->mode = mode>0 ? 1 : -1;
	}
	mode = f->mode;
	FUNLOCK(f);
	return mode;
}