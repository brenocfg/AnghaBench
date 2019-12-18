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
typedef  int /*<<< orphan*/  mbuf_class_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int m_maxlimit (int /*<<< orphan*/ ) ; 
 int m_peak (int /*<<< orphan*/ ) ; 
 int m_total (int /*<<< orphan*/ ) ; 
 scalar_t__ mb_peak_newreport ; 

__attribute__((used)) static boolean_t
mbuf_report_usage(mbuf_class_t cl)
{
	/* if a report is already in progress, nothing to do */
	if (mb_peak_newreport)
		return (TRUE);

	if (m_total(cl) > m_peak(cl) &&
	    m_total(cl) >= (m_maxlimit(cl) >> 4) &&
	    (m_total(cl) - m_peak(cl)) >= (m_peak(cl) >> 5))
		return (TRUE);
	return (FALSE);
}