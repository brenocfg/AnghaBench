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
struct m_tag {int dummy; } ;
struct ipsec_tag {scalar_t__ history_count; int /*<<< orphan*/ * socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_tag_delete (struct mbuf*,struct m_tag*) ; 

__attribute__((used)) static void
ipsec_optaux(
	struct mbuf			*m,
	struct ipsec_tag	*itag)
{
	if (itag && itag->socket == NULL && itag->history_count == 0) {
		m_tag_delete(m, ((struct m_tag*)itag) - 1);
	}
}