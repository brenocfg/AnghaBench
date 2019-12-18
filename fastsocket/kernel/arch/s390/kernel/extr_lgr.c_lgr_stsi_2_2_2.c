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
struct sysinfo_2_2_2 {int /*<<< orphan*/  lpar_number; int /*<<< orphan*/  name; } ;
struct lgr_info {int /*<<< orphan*/  lpar_number; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  cpascii (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lgr_page ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stsi (struct sysinfo_2_2_2*,int,int,int) ; 

__attribute__((used)) static void lgr_stsi_2_2_2(struct lgr_info *lgr_info)
{
	struct sysinfo_2_2_2 *si = (void *) lgr_page;

	if (stsi(si, 2, 2, 2) == -ENOSYS)
		return;
	cpascii(lgr_info->name, si->name, sizeof(si->name));
	memcpy(&lgr_info->lpar_number, &si->lpar_number,
	       sizeof(lgr_info->lpar_number));
}