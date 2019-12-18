#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct svc_fh {TYPE_2__* fh_export; scalar_t__ fh_want_write; } ;
struct TYPE_3__ {int /*<<< orphan*/  mnt; } ;
struct TYPE_4__ {TYPE_1__ ex_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  mnt_drop_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fh_drop_write(struct svc_fh *fh)
{
	if (fh->fh_want_write) {
		fh->fh_want_write = 0;
		mnt_drop_write(fh->fh_export->ex_path.mnt);
	}
}