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
struct o2net_sock_container {scalar_t__ sc_handshake_ok; int sc_page_off; int /*<<< orphan*/  sc_tv_advance_stop; int /*<<< orphan*/  sc_sock; int /*<<< orphan*/  sc_page; int /*<<< orphan*/  sc_tv_advance_start; } ;
struct o2net_msg {int /*<<< orphan*/  data_len; } ;
struct o2net_handshake {int dummy; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int EPROTO ; 
 int O2NET_MAX_PAYLOAD_BYTES ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msglog (struct o2net_msg*,char*,int) ; 
 int /*<<< orphan*/  o2net_check_handshake (struct o2net_sock_container*) ; 
 int o2net_process_message (struct o2net_sock_container*,struct o2net_msg*) ; 
 int o2net_recv_tcp_msg (int /*<<< orphan*/ ,void*,size_t) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sclog (struct o2net_sock_container*,char*,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int o2net_advance_rx(struct o2net_sock_container *sc)
{
	struct o2net_msg *hdr;
	int ret = 0;
	void *data;
	size_t datalen;

	sclog(sc, "receiving\n");
	do_gettimeofday(&sc->sc_tv_advance_start);

	if (unlikely(sc->sc_handshake_ok == 0)) {
		if(sc->sc_page_off < sizeof(struct o2net_handshake)) {
			data = page_address(sc->sc_page) + sc->sc_page_off;
			datalen = sizeof(struct o2net_handshake) - sc->sc_page_off;
			ret = o2net_recv_tcp_msg(sc->sc_sock, data, datalen);
			if (ret > 0)
				sc->sc_page_off += ret;
		}

		if (sc->sc_page_off == sizeof(struct o2net_handshake)) {
			o2net_check_handshake(sc);
			if (unlikely(sc->sc_handshake_ok == 0))
				ret = -EPROTO;
		}
		goto out;
	}

	/* do we need more header? */
	if (sc->sc_page_off < sizeof(struct o2net_msg)) {
		data = page_address(sc->sc_page) + sc->sc_page_off;
		datalen = sizeof(struct o2net_msg) - sc->sc_page_off;
		ret = o2net_recv_tcp_msg(sc->sc_sock, data, datalen);
		if (ret > 0) {
			sc->sc_page_off += ret;
			/* only swab incoming here.. we can
			 * only get here once as we cross from
			 * being under to over */
			if (sc->sc_page_off == sizeof(struct o2net_msg)) {
				hdr = page_address(sc->sc_page);
				if (be16_to_cpu(hdr->data_len) >
				    O2NET_MAX_PAYLOAD_BYTES)
					ret = -EOVERFLOW;
			}
		}
		if (ret <= 0)
			goto out;
	}

	if (sc->sc_page_off < sizeof(struct o2net_msg)) {
		/* oof, still don't have a header */
		goto out;
	}

	/* this was swabbed above when we first read it */
	hdr = page_address(sc->sc_page);

	msglog(hdr, "at page_off %zu\n", sc->sc_page_off);

	/* do we need more payload? */
	if (sc->sc_page_off - sizeof(struct o2net_msg) < be16_to_cpu(hdr->data_len)) {
		/* need more payload */
		data = page_address(sc->sc_page) + sc->sc_page_off;
		datalen = (sizeof(struct o2net_msg) + be16_to_cpu(hdr->data_len)) -
			  sc->sc_page_off;
		ret = o2net_recv_tcp_msg(sc->sc_sock, data, datalen);
		if (ret > 0)
			sc->sc_page_off += ret;
		if (ret <= 0)
			goto out;
	}

	if (sc->sc_page_off - sizeof(struct o2net_msg) == be16_to_cpu(hdr->data_len)) {
		/* we can only get here once, the first time we read
		 * the payload.. so set ret to progress if the handler
		 * works out. after calling this the message is toast */
		ret = o2net_process_message(sc, hdr);
		if (ret == 0)
			ret = 1;
		sc->sc_page_off = 0;
	}

out:
	sclog(sc, "ret = %d\n", ret);
	do_gettimeofday(&sc->sc_tv_advance_stop);
	return ret;
}