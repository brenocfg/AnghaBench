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
struct pr_usrreqs {int /*<<< orphan*/ * pru_preconnect; int /*<<< orphan*/ * pru_socheckopt; int /*<<< orphan*/ * pru_sosend_list; int /*<<< orphan*/ * pru_sosend; int /*<<< orphan*/ * pru_soreceive_list; int /*<<< orphan*/ * pru_soreceive; int /*<<< orphan*/ * pru_sopoll; int /*<<< orphan*/ * pru_sockaddr; int /*<<< orphan*/ * pru_shutdown; int /*<<< orphan*/ * pru_sense; int /*<<< orphan*/ * pru_send_list; int /*<<< orphan*/ * pru_send; int /*<<< orphan*/ * pru_rcvoob; int /*<<< orphan*/ * pru_rcvd; int /*<<< orphan*/ * pru_peeraddr; int /*<<< orphan*/ * pru_listen; int /*<<< orphan*/ * pru_disconnectx; int /*<<< orphan*/ * pru_disconnect; int /*<<< orphan*/ * pru_detach; int /*<<< orphan*/ * pru_control; int /*<<< orphan*/ * pru_connectx; int /*<<< orphan*/ * pru_connect2; int /*<<< orphan*/ * pru_connect; int /*<<< orphan*/ * pru_bind; int /*<<< orphan*/ * pru_attach; int /*<<< orphan*/ * pru_accept; int /*<<< orphan*/ * pru_abort; } ;

/* Variables and functions */
 int /*<<< orphan*/ * pru_abort_notsupp ; 
 int /*<<< orphan*/ * pru_accept_notsupp ; 
 int /*<<< orphan*/ * pru_attach_notsupp ; 
 int /*<<< orphan*/ * pru_bind_notsupp ; 
 int /*<<< orphan*/ * pru_connect2_notsupp ; 
 int /*<<< orphan*/ * pru_connect_notsupp ; 
 int /*<<< orphan*/ * pru_connectx_notsupp ; 
 int /*<<< orphan*/ * pru_control_notsupp ; 
 int /*<<< orphan*/ * pru_detach_notsupp ; 
 int /*<<< orphan*/ * pru_disconnect_notsupp ; 
 int /*<<< orphan*/ * pru_disconnectx_notsupp ; 
 int /*<<< orphan*/ * pru_listen_notsupp ; 
 int /*<<< orphan*/ * pru_peeraddr_notsupp ; 
 int /*<<< orphan*/ * pru_preconnect_null ; 
 int /*<<< orphan*/ * pru_rcvd_notsupp ; 
 int /*<<< orphan*/ * pru_rcvoob_notsupp ; 
 int /*<<< orphan*/ * pru_send_list_notsupp ; 
 int /*<<< orphan*/ * pru_send_notsupp ; 
 int /*<<< orphan*/ * pru_sense_null ; 
 int /*<<< orphan*/ * pru_shutdown_notsupp ; 
 int /*<<< orphan*/ * pru_socheckopt_null ; 
 int /*<<< orphan*/ * pru_sockaddr_notsupp ; 
 int /*<<< orphan*/ * pru_sopoll_notsupp ; 
 int /*<<< orphan*/ * pru_soreceive_list_notsupp ; 
 int /*<<< orphan*/ * pru_soreceive_notsupp ; 
 int /*<<< orphan*/ * pru_sosend_list_notsupp ; 
 int /*<<< orphan*/ * pru_sosend_notsupp ; 

void
pru_sanitize(struct pr_usrreqs *pru)
{
#define	DEFAULT(foo, bar)	if ((foo) == NULL) (foo) = (bar)
	DEFAULT(pru->pru_abort, pru_abort_notsupp);
	DEFAULT(pru->pru_accept, pru_accept_notsupp);
	DEFAULT(pru->pru_attach, pru_attach_notsupp);
	DEFAULT(pru->pru_bind, pru_bind_notsupp);
	DEFAULT(pru->pru_connect, pru_connect_notsupp);
	DEFAULT(pru->pru_connect2, pru_connect2_notsupp);
	DEFAULT(pru->pru_connectx, pru_connectx_notsupp);
	DEFAULT(pru->pru_control, pru_control_notsupp);
	DEFAULT(pru->pru_detach, pru_detach_notsupp);
	DEFAULT(pru->pru_disconnect, pru_disconnect_notsupp);
	DEFAULT(pru->pru_disconnectx, pru_disconnectx_notsupp);
	DEFAULT(pru->pru_listen, pru_listen_notsupp);
	DEFAULT(pru->pru_peeraddr, pru_peeraddr_notsupp);
	DEFAULT(pru->pru_rcvd, pru_rcvd_notsupp);
	DEFAULT(pru->pru_rcvoob, pru_rcvoob_notsupp);
	DEFAULT(pru->pru_send, pru_send_notsupp);
	DEFAULT(pru->pru_send_list, pru_send_list_notsupp);
	DEFAULT(pru->pru_sense, pru_sense_null);
	DEFAULT(pru->pru_shutdown, pru_shutdown_notsupp);
	DEFAULT(pru->pru_sockaddr, pru_sockaddr_notsupp);
	DEFAULT(pru->pru_sopoll, pru_sopoll_notsupp);
	DEFAULT(pru->pru_soreceive, pru_soreceive_notsupp);
	DEFAULT(pru->pru_soreceive_list, pru_soreceive_list_notsupp);
	DEFAULT(pru->pru_sosend, pru_sosend_notsupp);
	DEFAULT(pru->pru_sosend_list, pru_sosend_list_notsupp);
	DEFAULT(pru->pru_socheckopt, pru_socheckopt_null);
	DEFAULT(pru->pru_preconnect, pru_preconnect_null);
#undef DEFAULT
}