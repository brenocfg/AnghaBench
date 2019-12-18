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
struct lcs_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_HEX (int,int /*<<< orphan*/ ,struct lcs_card**,int) ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct lcs_card*) ; 
 int /*<<< orphan*/  setup ; 

__attribute__((used)) static void
lcs_free_card(struct lcs_card *card)
{
	LCS_DBF_TEXT(2, setup, "remcard");
	LCS_DBF_HEX(2, setup, &card, sizeof(void*));
	kfree(card);
}