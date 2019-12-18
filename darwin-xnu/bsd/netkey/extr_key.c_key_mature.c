#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct secasvar {int flags; int /*<<< orphan*/  alg_enc; TYPE_4__* key_enc; TYPE_3__* key_auth; int /*<<< orphan*/  alg_auth; int /*<<< orphan*/  spi; TYPE_2__* sah; } ;
struct ipcomp_algorithm {int dummy; } ;
struct esp_algorithm {int keymin; int keymax; scalar_t__ (* mature ) (struct secasvar*) ;} ;
struct ah_algorithm {int keymin; int keymax; scalar_t__ (* mature ) (struct secasvar*) ;} ;
struct TYPE_8__ {int sadb_key_bits; } ;
struct TYPE_7__ {int sadb_key_bits; } ;
struct TYPE_5__ {int proto; } ;
struct TYPE_6__ {TYPE_1__ saidx; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
#define  IPPROTO_AH 130 
#define  IPPROTO_ESP 129 
#define  IPPROTO_IPCOMP 128 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  SADB_AALG_NONE ; 
 int /*<<< orphan*/  SADB_EALG_NONE ; 
 int /*<<< orphan*/  SADB_SASTATE_MATURE ; 
 int SADB_SATYPE_AH ; 
 int SADB_SATYPE_ESP ; 
 int SADB_X_EXT_DERIV ; 
 int SADB_X_EXT_OLD ; 
 int SADB_X_EXT_RAWCPI ; 
 struct ah_algorithm* ah_algorithm_lookup (int /*<<< orphan*/ ) ; 
 struct esp_algorithm* esp_algorithm_lookup (int /*<<< orphan*/ ) ; 
 struct ipcomp_algorithm* ipcomp_algorithm_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipseclog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_sa_chgstate (struct secasvar*,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sadb_mutex ; 
 scalar_t__ stub1 (struct secasvar*) ; 
 scalar_t__ stub2 (struct secasvar*) ; 

__attribute__((used)) static int
key_mature(
		   struct secasvar *sav)
{
	int mature;
	int checkmask = 0;	/* 2^0: ealg  2^1: aalg  2^2: calg */
	int mustmask = 0;	/* 2^0: ealg  2^1: aalg  2^2: calg */
	
	mature = 0;
	
	LCK_MTX_ASSERT(sadb_mutex, LCK_MTX_ASSERT_OWNED);
	
	/* check SPI value */
	switch (sav->sah->saidx.proto) {
		case IPPROTO_ESP:
		case IPPROTO_AH:
			
			/* No reason to test if this is >= 0, because ntohl(sav->spi) is unsigned. */
			if (ntohl(sav->spi) <= 255) {
				ipseclog((LOG_DEBUG,
						  "key_mature: illegal range of SPI %u.\n",
						  (u_int32_t)ntohl(sav->spi)));
				return EINVAL;
			}
			break;
	}
	
	/* check satype */
	switch (sav->sah->saidx.proto) {
		case IPPROTO_ESP:
			/* check flags */
			if ((sav->flags & SADB_X_EXT_OLD)
				&& (sav->flags & SADB_X_EXT_DERIV)) {
				ipseclog((LOG_DEBUG, "key_mature: "
						  "invalid flag (derived) given to old-esp.\n"));
				return EINVAL;
			}
			if (sav->alg_auth == SADB_AALG_NONE)
				checkmask = 1;
			else
				checkmask = 3;
			mustmask = 1;
			break;
		case IPPROTO_AH:
			/* check flags */
			if (sav->flags & SADB_X_EXT_DERIV) {
				ipseclog((LOG_DEBUG, "key_mature: "
						  "invalid flag (derived) given to AH SA.\n"));
				return EINVAL;
			}
			if (sav->alg_enc != SADB_EALG_NONE) {
				ipseclog((LOG_DEBUG, "key_mature: "
						  "protocol and algorithm mismated.\n"));
				return(EINVAL);
			}
			checkmask = 2;
			mustmask = 2;
			break;
		case IPPROTO_IPCOMP:
			if (sav->alg_auth != SADB_AALG_NONE) {
				ipseclog((LOG_DEBUG, "key_mature: "
						  "protocol and algorithm mismated.\n"));
				return(EINVAL);
			}
			if ((sav->flags & SADB_X_EXT_RAWCPI) == 0
				&& ntohl(sav->spi) >= 0x10000) {
				ipseclog((LOG_DEBUG, "key_mature: invalid cpi for IPComp.\n"));
				return(EINVAL);
			}
			checkmask = 4;
			mustmask = 4;
			break;
		default:
			ipseclog((LOG_DEBUG, "key_mature: Invalid satype.\n"));
			return EPROTONOSUPPORT;
	}
	
	/* check authentication algorithm */
	if ((checkmask & 2) != 0) {
		const struct ah_algorithm *algo;
		int keylen;
		
		algo = ah_algorithm_lookup(sav->alg_auth);
		if (!algo) {
			ipseclog((LOG_DEBUG,"key_mature: "
					  "unknown authentication algorithm.\n"));
			return EINVAL;
		}
		
		/* algorithm-dependent check */
		if (sav->key_auth)
			keylen = sav->key_auth->sadb_key_bits;
		else
			keylen = 0;
		if (keylen < algo->keymin || algo->keymax < keylen) {
			ipseclog((LOG_DEBUG,
					  "key_mature: invalid AH key length %d "
					  "(%d-%d allowed)\n",
					  keylen, algo->keymin, algo->keymax));
			return EINVAL;
		}
		
		if (algo->mature) {
			if ((*algo->mature)(sav)) {
				/* message generated in per-algorithm function*/
				return EINVAL;
			} else
				mature = SADB_SATYPE_AH;
		}
		
		if ((mustmask & 2) != 0 &&  mature != SADB_SATYPE_AH) {
			ipseclog((LOG_DEBUG, "key_mature: no satisfy algorithm for AH\n"));
			return EINVAL;
		}
	}
	
	/* check encryption algorithm */
	if ((checkmask & 1) != 0) {
#if IPSEC_ESP
		const struct esp_algorithm *algo;
		int keylen;
		
		algo = esp_algorithm_lookup(sav->alg_enc);
		if (!algo) {
			ipseclog((LOG_DEBUG, "key_mature: unknown encryption algorithm.\n"));
			return EINVAL;
		}
		
		/* algorithm-dependent check */
		if (sav->key_enc)
			keylen = sav->key_enc->sadb_key_bits;
		else
			keylen = 0;
		if (keylen < algo->keymin || algo->keymax < keylen) {
			ipseclog((LOG_DEBUG,
					  "key_mature: invalid ESP key length %d "
					  "(%d-%d allowed)\n",
					  keylen, algo->keymin, algo->keymax));
			return EINVAL;
		}
		
		if (algo->mature) {
			if ((*algo->mature)(sav)) {
				/* message generated in per-algorithm function*/
				return EINVAL;
			} else
				mature = SADB_SATYPE_ESP;
		}
		
		if ((mustmask & 1) != 0 &&  mature != SADB_SATYPE_ESP) {
			ipseclog((LOG_DEBUG, "key_mature: no satisfy algorithm for ESP\n"));
			return EINVAL;
		}
#else /*IPSEC_ESP*/
		ipseclog((LOG_DEBUG, "key_mature: ESP not supported in this configuration\n"));
		return EINVAL;
#endif
	}
	
	/* check compression algorithm */
	if ((checkmask & 4) != 0) {
		const struct ipcomp_algorithm *algo;
		
		/* algorithm-dependent check */
		algo = ipcomp_algorithm_lookup(sav->alg_enc);
		if (!algo) {
			ipseclog((LOG_DEBUG, "key_mature: unknown compression algorithm.\n"));
			return EINVAL;
		}
	}
	
	key_sa_chgstate(sav, SADB_SASTATE_MATURE);
	
	return 0;
}