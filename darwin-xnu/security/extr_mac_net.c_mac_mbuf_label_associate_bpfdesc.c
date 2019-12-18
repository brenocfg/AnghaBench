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
struct label {int dummy; } ;
struct bpf_d {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,struct bpf_d*,struct label*,struct mbuf*,struct label*) ; 
 struct label* mac_bpfdesc_label_get (struct bpf_d*) ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_label_associate_bpfdesc ; 

void
mac_mbuf_label_associate_bpfdesc(struct bpf_d *bpf_d, struct mbuf *mbuf)
{
	struct label *m_label, *b_label;

	/* bpf_d must be locked */

	m_label = mac_mbuf_to_label(mbuf);
	b_label = mac_bpfdesc_label_get(bpf_d);

	MAC_PERFORM(mbuf_label_associate_bpfdesc, bpf_d, b_label, mbuf,
	    m_label);
}