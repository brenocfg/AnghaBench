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
typedef  int /*<<< orphan*/  voidp ;
struct TYPE_3__ {int /*<<< orphan*/  fs_flags; } ;
typedef  TYPE_1__ fserver ;

/* Variables and functions */
 int /*<<< orphan*/  FSF_WANT ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
wakeup_srvr(fserver *fs)
{
  fs->fs_flags &= ~FSF_WANT;
  wakeup((voidp) fs);
}