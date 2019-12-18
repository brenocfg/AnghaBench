#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_4__ {int showall; scalar_t__* company; scalar_t__* gamecode; scalar_t__* filename; scalar_t__ filelen; scalar_t__ fileno; int /*<<< orphan*/  chn; } ;
typedef  TYPE_1__ card_dir ;

/* Variables and functions */
 int /*<<< orphan*/  __card_findnext (TYPE_1__*) ; 

s32 CARD_FindFirst(s32 chn, card_dir *dir, bool showall)
{
	// initialise structure
	dir->chn = chn;
	dir->fileno = 0;
	dir->filelen = 0;
	dir->filename[0] = 0;
	dir->gamecode[0] = 0;
	dir->company[0] = 0;
	dir->showall = showall;
	return __card_findnext(dir);
}