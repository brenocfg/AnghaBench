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
struct cumanascsi2_info {int terms; scalar_t__ base; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALATCH_DIS_TERM ; 
 int /*<<< orphan*/  ALATCH_ENA_TERM ; 
 scalar_t__ CUMANASCSI2_ALATCH ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
cumanascsi_2_terminator_ctl(struct Scsi_Host *host, int on_off)
{
	struct cumanascsi2_info *info = (struct cumanascsi2_info *)host->hostdata;

	if (on_off) {
		info->terms = 1;
		writeb(ALATCH_ENA_TERM, info->base + CUMANASCSI2_ALATCH);
	} else {
		info->terms = 0;
		writeb(ALATCH_DIS_TERM, info->base + CUMANASCSI2_ALATCH);
	}
}