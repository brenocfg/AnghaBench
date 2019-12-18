#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
union sctp_addr_param {int crr_id; TYPE_2__ param_hdr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin_family; } ;
union sctp_addr {TYPE_1__ v4; } ;
struct sockaddr {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
struct sctp_af {int (* to_addr_param ) (union sctp_addr*,union sctp_addr_param*) ;int /*<<< orphan*/  sockaddr_len; } ;
typedef  union sctp_addr_param sctp_addip_param_t ;
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,union sctp_addr_param*) ; 
 struct sctp_af* sctp_get_af_specific (int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_asconf (struct sctp_association*,union sctp_addr*,int) ; 
 int stub1 (union sctp_addr*,union sctp_addr_param*) ; 
 int stub2 (union sctp_addr*,union sctp_addr_param*) ; 

struct sctp_chunk *sctp_make_asconf_update_ip(struct sctp_association *asoc,
					      union sctp_addr	      *laddr,
					      struct sockaddr	      *addrs,
					      int		      addrcnt,
					      __be16		      flags)
{
	sctp_addip_param_t	param;
	struct sctp_chunk	*retval;
	union sctp_addr_param	addr_param;
	union sctp_addr		*addr;
	void			*addr_buf;
	struct sctp_af		*af;
	int			paramlen = sizeof(param);
	int			addr_param_len = 0;
	int 			totallen = 0;
	int 			i;

	/* Get total length of all the address parameters. */
	addr_buf = addrs;
	for (i = 0; i < addrcnt; i++) {
		addr = (union sctp_addr *)addr_buf;
		af = sctp_get_af_specific(addr->v4.sin_family);
		addr_param_len = af->to_addr_param(addr, &addr_param);

		totallen += paramlen;
		totallen += addr_param_len;

		addr_buf += af->sockaddr_len;
	}

	/* Create an asconf chunk with the required length. */
	retval = sctp_make_asconf(asoc, laddr, totallen);
	if (!retval)
		return NULL;

	/* Add the address parameters to the asconf chunk. */
	addr_buf = addrs;
	for (i = 0; i < addrcnt; i++) {
		addr = (union sctp_addr *)addr_buf;
		af = sctp_get_af_specific(addr->v4.sin_family);
		addr_param_len = af->to_addr_param(addr, &addr_param);
		param.param_hdr.type = flags;
		param.param_hdr.length = htons(paramlen + addr_param_len);
		param.crr_id = i;

		sctp_addto_chunk(retval, paramlen, &param);
		sctp_addto_chunk(retval, addr_param_len, &addr_param);

		addr_buf += af->sockaddr_len;
	}
	return retval;
}