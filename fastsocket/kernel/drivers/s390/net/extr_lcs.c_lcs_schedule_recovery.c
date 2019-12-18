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
struct lcs_card {int /*<<< orphan*/  kernel_thread_starter; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_RECOVERY_THREAD ; 
 int /*<<< orphan*/  lcs_set_thread_start_bit (struct lcs_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static void
lcs_schedule_recovery(struct lcs_card *card)
{
	LCS_DBF_TEXT(2, trace, "startrec");
	if (!lcs_set_thread_start_bit(card, LCS_RECOVERY_THREAD))
		schedule_work(&card->kernel_thread_starter);
}