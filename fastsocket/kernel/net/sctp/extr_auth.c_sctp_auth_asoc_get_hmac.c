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
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
struct sctp_hmac_algo_param {int /*<<< orphan*/ * hmac_ids; TYPE_2__ param_hdr; } ;
struct sctp_hmac {int /*<<< orphan*/  hmac_name; } ;
struct TYPE_3__ {struct sctp_hmac_algo_param* peer_hmacs; } ;
struct sctp_association {int default_hmac_id; TYPE_1__ peer; } ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int __u16 ;

/* Variables and functions */
 int SCTP_AUTH_HMAC_ID_MAX ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 struct sctp_hmac* sctp_hmac_list ; 

struct sctp_hmac *sctp_auth_asoc_get_hmac(const struct sctp_association *asoc)
{
	struct sctp_hmac_algo_param *hmacs;
	__u16 n_elt;
	__u16 id = 0;
	int i;

	/* If we have a default entry, use it */
	if (asoc->default_hmac_id)
		return &sctp_hmac_list[asoc->default_hmac_id];

	/* Since we do not have a default entry, find the first entry
	 * we support and return that.  Do not cache that id.
	 */
	hmacs = asoc->peer.peer_hmacs;
	if (!hmacs)
		return NULL;

	n_elt = (ntohs(hmacs->param_hdr.length) - sizeof(sctp_paramhdr_t)) >> 1;
	for (i = 0; i < n_elt; i++) {
		id = ntohs(hmacs->hmac_ids[i]);

		/* Check the id is in the supported range */
		if (id > SCTP_AUTH_HMAC_ID_MAX) {
			id = 0;
			continue;
		}

		/* See is we support the id.  Supported IDs have name and
		 * length fields set, so that we can allocated and use
		 * them.  We can safely just check for name, for without the
		 * name, we can't allocate the TFM.
		 */
		if (!sctp_hmac_list[id].hmac_name) {
			id = 0;
			continue;
		}

		break;
	}

	if (id == 0)
		return NULL;

	return &sctp_hmac_list[id];
}