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
typedef  int /*<<< orphan*/  UBYTE ;
struct TYPE_3__ {int sectorsize; int /*<<< orphan*/  fp; int /*<<< orphan*/  current_sector; } ;
typedef  TYPE_1__ ATR_Info ;

/* Variables and functions */
 int fsave (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_atr_sector(ATR_Info *pai, UBYTE *buf)
{
	return fsave(buf, pai->current_sector++ <= 3 ? 128 : pai->sectorsize, pai->fp);
}