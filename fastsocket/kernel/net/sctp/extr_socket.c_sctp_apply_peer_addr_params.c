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
struct sctp_transport {int param_flags; scalar_t__ pathmaxrxt; void* sackdelay; scalar_t__ pathmtu; void* hbinterval; int /*<<< orphan*/  asoc; } ;
struct sctp_sock {int param_flags; scalar_t__ pathmaxrxt; scalar_t__ sackdelay; scalar_t__ pathmtu; scalar_t__ hbinterval; } ;
struct sctp_paddrparams {int spp_flags; scalar_t__ spp_pathmaxrxt; scalar_t__ spp_sackdelay; scalar_t__ spp_pathmtu; scalar_t__ spp_hbinterval; } ;
struct sctp_association {int param_flags; scalar_t__ pathmaxrxt; void* sackdelay; scalar_t__ pathmtu; void* hbinterval; } ;

/* Variables and functions */
 int SPP_HB ; 
 int SPP_HB_DEMAND ; 
 int SPP_HB_ENABLE ; 
 int SPP_HB_TIME_IS_ZERO ; 
 int SPP_PMTUD ; 
 int SPP_PMTUD_DISABLE ; 
 int SPP_PMTUD_ENABLE ; 
 int SPP_SACKDELAY ; 
 int SPP_SACKDELAY_ENABLE ; 
 void* msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  sctp_assoc_sync_pmtu (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_frag_point (struct sctp_association*,scalar_t__) ; 
 int /*<<< orphan*/  sctp_opt2sk (struct sctp_sock*) ; 
 int sctp_primitive_REQUESTHEARTBEAT (int /*<<< orphan*/ ,struct sctp_transport*) ; 
 int /*<<< orphan*/  sctp_transport_pmtu (struct sctp_transport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_apply_peer_addr_params(struct sctp_paddrparams *params,
				       struct sctp_transport   *trans,
				       struct sctp_association *asoc,
				       struct sctp_sock        *sp,
				       int                      hb_change,
				       int                      pmtud_change,
				       int                      sackdelay_change)
{
	int error;

	if (params->spp_flags & SPP_HB_DEMAND && trans) {
		error = sctp_primitive_REQUESTHEARTBEAT (trans->asoc, trans);
		if (error)
			return error;
	}

	/* Note that unless the spp_flag is set to SPP_HB_ENABLE the value of
	 * this field is ignored.  Note also that a value of zero indicates
	 * the current setting should be left unchanged.
	 */
	if (params->spp_flags & SPP_HB_ENABLE) {

		/* Re-zero the interval if the SPP_HB_TIME_IS_ZERO is
		 * set.  This lets us use 0 value when this flag
		 * is set.
		 */
		if (params->spp_flags & SPP_HB_TIME_IS_ZERO)
			params->spp_hbinterval = 0;

		if (params->spp_hbinterval ||
		    (params->spp_flags & SPP_HB_TIME_IS_ZERO)) {
			if (trans) {
				trans->hbinterval =
				    msecs_to_jiffies(params->spp_hbinterval);
			} else if (asoc) {
				asoc->hbinterval =
				    msecs_to_jiffies(params->spp_hbinterval);
			} else {
				sp->hbinterval = params->spp_hbinterval;
			}
		}
	}

	if (hb_change) {
		if (trans) {
			trans->param_flags =
				(trans->param_flags & ~SPP_HB) | hb_change;
		} else if (asoc) {
			asoc->param_flags =
				(asoc->param_flags & ~SPP_HB) | hb_change;
		} else {
			sp->param_flags =
				(sp->param_flags & ~SPP_HB) | hb_change;
		}
	}

	/* When Path MTU discovery is disabled the value specified here will
	 * be the "fixed" path mtu (i.e. the value of the spp_flags field must
	 * include the flag SPP_PMTUD_DISABLE for this field to have any
	 * effect).
	 */
	if ((params->spp_flags & SPP_PMTUD_DISABLE) && params->spp_pathmtu) {
		if (trans) {
			trans->pathmtu = params->spp_pathmtu;
			sctp_assoc_sync_pmtu(asoc);
		} else if (asoc) {
			asoc->pathmtu = params->spp_pathmtu;
			sctp_frag_point(asoc, params->spp_pathmtu);
		} else {
			sp->pathmtu = params->spp_pathmtu;
		}
	}

	if (pmtud_change) {
		if (trans) {
			int update = (trans->param_flags & SPP_PMTUD_DISABLE) &&
				(params->spp_flags & SPP_PMTUD_ENABLE);
			trans->param_flags =
				(trans->param_flags & ~SPP_PMTUD) | pmtud_change;
			if (update) {
				sctp_transport_pmtu(trans, sctp_opt2sk(sp));
				sctp_assoc_sync_pmtu(asoc);
			}
		} else if (asoc) {
			asoc->param_flags =
				(asoc->param_flags & ~SPP_PMTUD) | pmtud_change;
		} else {
			sp->param_flags =
				(sp->param_flags & ~SPP_PMTUD) | pmtud_change;
		}
	}

	/* Note that unless the spp_flag is set to SPP_SACKDELAY_ENABLE the
	 * value of this field is ignored.  Note also that a value of zero
	 * indicates the current setting should be left unchanged.
	 */
	if ((params->spp_flags & SPP_SACKDELAY_ENABLE) && params->spp_sackdelay) {
		if (trans) {
			trans->sackdelay =
				msecs_to_jiffies(params->spp_sackdelay);
		} else if (asoc) {
			asoc->sackdelay =
				msecs_to_jiffies(params->spp_sackdelay);
		} else {
			sp->sackdelay = params->spp_sackdelay;
		}
	}

	if (sackdelay_change) {
		if (trans) {
			trans->param_flags =
				(trans->param_flags & ~SPP_SACKDELAY) |
				sackdelay_change;
		} else if (asoc) {
			asoc->param_flags =
				(asoc->param_flags & ~SPP_SACKDELAY) |
				sackdelay_change;
		} else {
			sp->param_flags =
				(sp->param_flags & ~SPP_SACKDELAY) |
				sackdelay_change;
		}
	}

	/* Note that a value of zero indicates the current setting should be
	   left unchanged.
	 */
	if (params->spp_pathmaxrxt) {
		if (trans) {
			trans->pathmaxrxt = params->spp_pathmaxrxt;
		} else if (asoc) {
			asoc->pathmaxrxt = params->spp_pathmaxrxt;
		} else {
			sp->pathmaxrxt = params->spp_pathmaxrxt;
		}
	}

	return 0;
}