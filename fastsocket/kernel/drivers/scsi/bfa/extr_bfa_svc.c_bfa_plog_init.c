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
struct bfa_plog_s {int plog_enabled; scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/  plog_sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_PL_SIG_LEN ; 
 int /*<<< orphan*/  BFA_PL_SIG_STR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void
bfa_plog_init(struct bfa_plog_s *plog)
{
	memset((char *)plog, 0, sizeof(struct bfa_plog_s));

	memcpy(plog->plog_sig, BFA_PL_SIG_STR, BFA_PL_SIG_LEN);
	plog->head = plog->tail = 0;
	plog->plog_enabled = 1;
}