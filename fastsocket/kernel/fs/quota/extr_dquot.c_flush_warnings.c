#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dquot {TYPE_1__* dq_sb; int /*<<< orphan*/  dq_id; int /*<<< orphan*/  dq_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int MAXQUOTAS ; 
 char QUOTA_NL_NOWARN ; 
 int /*<<< orphan*/  print_warning (struct dquot*,char) ; 
 int /*<<< orphan*/  quota_send_warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  warning_issued (struct dquot*,char) ; 

__attribute__((used)) static void flush_warnings(struct dquot *const *dquots, char *warntype)
{
	struct dquot *dq;
	int i;

	for (i = 0; i < MAXQUOTAS; i++) {
		dq = dquots[i];
		if (dq && warntype[i] != QUOTA_NL_NOWARN &&
		    !warning_issued(dq, warntype[i])) {
#ifdef CONFIG_PRINT_QUOTA_WARNING
			print_warning(dq, warntype[i]);
#endif
			quota_send_warning(dq->dq_type, dq->dq_id,
					   dq->dq_sb->s_dev, warntype[i]);
		}
	}
}