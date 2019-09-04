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
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;
struct m_tag {int dummy; } ;
struct cfil_tag {short cfil_so_options; int /*<<< orphan*/  cfil_faddr; int /*<<< orphan*/  cfil_so_state_change_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_MODULE_TAG_ID ; 
 int /*<<< orphan*/  KERNEL_TAG_TYPE_CFIL_UDP ; 
 struct m_tag* m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_tag_unlink (struct mbuf*,struct m_tag*) ; 

struct m_tag *
cfil_udp_get_socket_state(struct mbuf *m, uint32_t *state_change_cnt, short *options,
						  struct sockaddr **faddr)
{
	struct m_tag *tag = NULL;
	struct cfil_tag *ctag = NULL;

	tag = m_tag_locate(m, KERNEL_MODULE_TAG_ID, KERNEL_TAG_TYPE_CFIL_UDP, NULL);
	if (tag) {
		ctag = (struct cfil_tag *)(tag + 1);
		if (state_change_cnt)
			*state_change_cnt = ctag->cfil_so_state_change_cnt;
		if (options)
			*options = ctag->cfil_so_options;
		if (faddr)
			*faddr = (struct sockaddr *) &ctag->cfil_faddr;

		/*
		 * Unlink tag and hand it over to caller.
		 * Note that caller will be responsible to free it.
		 */
		m_tag_unlink(m, tag);
		return tag;
	}
	return NULL;
}