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
struct powertec_info {scalar_t__ base; int /*<<< orphan*/  term_ctl; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 scalar_t__ POWERTEC_TERM_CONTROL ; 
 int /*<<< orphan*/  POWERTEC_TERM_ENABLE ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
powertecscsi_terminator_ctl(struct Scsi_Host *host, int on_off)
{
	struct powertec_info *info = (struct powertec_info *)host->hostdata;

	info->term_ctl = on_off ? POWERTEC_TERM_ENABLE : 0;
	writeb(info->term_ctl, info->base + POWERTEC_TERM_CONTROL);
}