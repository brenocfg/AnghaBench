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
struct cfil_info {int /*<<< orphan*/ * cfi_entries; int /*<<< orphan*/  cfi_rcv; int /*<<< orphan*/  cfi_snd; } ;

/* Variables and functions */
 int MAX_CONTENT_FILTER ; 
 int /*<<< orphan*/  cfil_entry_verify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_info_buf_verify (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfil_info_verify(struct cfil_info *cfil_info)
{
	int i;

	if (cfil_info == NULL)
		return;

	cfil_info_buf_verify(&cfil_info->cfi_snd);
	cfil_info_buf_verify(&cfil_info->cfi_rcv);

	for (i = 0; i < MAX_CONTENT_FILTER; i++)
		cfil_entry_verify(&cfil_info->cfi_entries[i]);
}