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
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
union sctp_addr_param {scalar_t__ crr_id; TYPE_1__ param_hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_family; } ;
union sctp_addr {TYPE_2__ v4; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
struct sctp_af {int (* to_addr_param ) (union sctp_addr*,union sctp_addr_param*) ;} ;
typedef  union sctp_addr_param sctp_addip_param_t ;
typedef  int /*<<< orphan*/  param ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_PARAM_SET_PRIMARY ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,union sctp_addr_param*) ; 
 struct sctp_af* sctp_get_af_specific (int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_asconf (struct sctp_association*,union sctp_addr*,int) ; 
 int stub1 (union sctp_addr*,union sctp_addr_param*) ; 

struct sctp_chunk *sctp_make_asconf_set_prim(struct sctp_association *asoc,
					     union sctp_addr *addr)
{
	sctp_addip_param_t	param;
	struct sctp_chunk 	*retval;
	int 			len = sizeof(param);
	union sctp_addr_param	addrparam;
	int			addrlen;
	struct sctp_af		*af = sctp_get_af_specific(addr->v4.sin_family);

	addrlen = af->to_addr_param(addr, &addrparam);
	if (!addrlen)
		return NULL;
	len += addrlen;

	/* Create the chunk and make asconf header. */
	retval = sctp_make_asconf(asoc, addr, len);
	if (!retval)
		return NULL;

	param.param_hdr.type = SCTP_PARAM_SET_PRIMARY;
	param.param_hdr.length = htons(len);
	param.crr_id = 0;

	sctp_addto_chunk(retval, sizeof(param), &param);
	sctp_addto_chunk(retval, addrlen, &addrparam);

	return retval;
}