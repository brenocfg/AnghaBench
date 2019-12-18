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
struct TYPE_3__ {int /*<<< orphan*/  h_lochost; } ;
typedef  TYPE_1__ host ;

/* Variables and functions */
 int /*<<< orphan*/  autodir ; 
 int /*<<< orphan*/  xsnprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void
compute_automount_point(char *buf, size_t l, host *hp, char *vn)
{
  xsnprintf(buf, l, "%s/%s%s", autodir, hp->h_lochost, vn);
}