#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ u_long ;
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_blocks; scalar_t__ st_ino; } ;
struct TYPE_3__ {int /*<<< orphan*/  fts_name; struct stat* fts_statp; } ;
typedef  TYPE_1__ FTSENT ;

/* Variables and functions */
 int /*<<< orphan*/  blocksize ; 
 int colortype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endcolor (int /*<<< orphan*/ ) ; 
 scalar_t__ f_color ; 
 scalar_t__ f_inode ; 
 scalar_t__ f_size ; 
 scalar_t__ f_type ; 
 int /*<<< orphan*/  howmany (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ printname (int /*<<< orphan*/ ) ; 
 scalar_t__ printtype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
printaname(const FTSENT *p, u_long inodefield, u_long sizefield)
{
	struct stat *sp;
	int chcnt;
#ifdef COLORLS
	int color_printed = 0;
#endif

	sp = p->fts_statp;
	chcnt = 0;
	if (f_inode)
		chcnt += printf("%*ju ",
		    (int)inodefield, (uintmax_t)sp->st_ino);
	if (f_size)
		chcnt += printf("%*jd ",
		    (int)sizefield, howmany(sp->st_blocks, blocksize));
#ifdef COLORLS
	if (f_color)
		color_printed = colortype(sp->st_mode);
#endif
	chcnt += printname(p->fts_name);
#ifdef COLORLS
	if (f_color && color_printed)
		endcolor(0);
#endif
	if (f_type)
		chcnt += printtype(sp->st_mode);
	return (chcnt);
}