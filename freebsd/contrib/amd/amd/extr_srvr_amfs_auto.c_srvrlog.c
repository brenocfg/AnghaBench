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
struct TYPE_3__ {int /*<<< orphan*/  fs_type; int /*<<< orphan*/  fs_host; } ;
typedef  TYPE_1__ fserver ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
srvrlog(fserver *fs, char *state)
{
  plog(XLOG_INFO, "file server %s, type %s, state %s", fs->fs_host, fs->fs_type, state);
}