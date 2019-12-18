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
struct qib_devdata {int rcvegrbufsize; scalar_t__ tidinvalid; int /*<<< orphan*/  tidtemplate; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBA7220_TID_SZ_2K ; 
 int /*<<< orphan*/  IBA7220_TID_SZ_4K ; 

__attribute__((used)) static void qib_7220_tidtemplate(struct qib_devdata *dd)
{
	if (dd->rcvegrbufsize == 2048)
		dd->tidtemplate = IBA7220_TID_SZ_2K;
	else if (dd->rcvegrbufsize == 4096)
		dd->tidtemplate = IBA7220_TID_SZ_4K;
	dd->tidinvalid = 0;
}