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
struct mbuf {int dummy; } ;
struct ipsec_tag {int history_count; struct ipsec_history* history; } ;
struct ipsec_history {int dummy; } ;

/* Variables and functions */
 struct ipsec_tag* ipsec_findaux (struct mbuf*) ; 

struct ipsec_history *
ipsec_gethist(
	struct mbuf *m,
	int *lenp)
{
	struct ipsec_tag	*itag;
	
	itag = ipsec_findaux(m);
	if (!itag)
		return NULL;
	if (itag->history_count == 0)
		return NULL;
	if (lenp)
		*lenp = (int)(itag->history_count * sizeof(struct ipsec_history));
	return itag->history;
}