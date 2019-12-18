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
struct pppol2tp_session {scalar_t__ send_seq; } ;

/* Variables and functions */
 int PPPOL2TP_L2TP_HDR_SIZE_NOSEQ ; 
 int PPPOL2TP_L2TP_HDR_SIZE_SEQ ; 

__attribute__((used)) static inline int pppol2tp_l2tp_header_len(struct pppol2tp_session *session)
{
	if (session->send_seq)
		return PPPOL2TP_L2TP_HDR_SIZE_SEQ;

	return PPPOL2TP_L2TP_HDR_SIZE_NOSEQ;
}