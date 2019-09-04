#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct secasvar {int flags; int alg_enc; TYPE_1__* key_enc; } ;
struct esp_algorithm {int keymin; int keymax; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int sadb_key_bits; } ;

/* Variables and functions */
 int ESP_AESGCM_KEYLEN128 ; 
 int ESP_AESGCM_KEYLEN192 ; 
 int ESP_AESGCM_KEYLEN256 ; 
 int /*<<< orphan*/  LOG_ERR ; 
#define  SADB_X_EALG_AES_GCM 128 
 int SADB_X_EXT_DERIV ; 
 int SADB_X_EXT_IIV ; 
 int SADB_X_EXT_OLD ; 
 struct esp_algorithm* esp_algorithm_lookup (int) ; 
 int /*<<< orphan*/  ipseclog (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
esp_gcm_mature(struct secasvar *sav)
{
	int keylen;
	const struct esp_algorithm *algo;

	if (sav->flags & SADB_X_EXT_OLD) {
		ipseclog((LOG_ERR,
		    "esp_gcm_mature: algorithm incompatible with esp-old\n"));
		return 1;
	}
	if (sav->flags & SADB_X_EXT_DERIV) {
		ipseclog((LOG_ERR,
		    "esp_gcm_mature: algorithm incompatible with derived\n"));
		return 1;
	}
	if (sav->flags & SADB_X_EXT_IIV) {
		ipseclog((LOG_ERR,
		    "esp_gcm_mature: implicit IV not currently implemented\n"));
		return 1;
	}

	if (!sav->key_enc) {
		ipseclog((LOG_ERR, "esp_gcm_mature: no key is given.\n"));
		return 1;
	}

	algo = esp_algorithm_lookup(sav->alg_enc);
	if (!algo) {
		ipseclog((LOG_ERR,
		    "esp_gcm_mature: unsupported algorithm.\n"));
		return 1;
	}

	keylen = sav->key_enc->sadb_key_bits;
	if (keylen < algo->keymin || algo->keymax < keylen) {
		ipseclog((LOG_ERR,
		    "esp_gcm_mature %s: invalid key length %d.\n",
		    algo->name, sav->key_enc->sadb_key_bits));
		return 1;
	}
	switch (sav->alg_enc) {
	case SADB_X_EALG_AES_GCM:
		/* allows specific key sizes only */
		if (!(keylen == ESP_AESGCM_KEYLEN128 || keylen == ESP_AESGCM_KEYLEN192 || keylen == ESP_AESGCM_KEYLEN256)) {
			ipseclog((LOG_ERR,
			    "esp_gcm_mature %s: invalid key length %d.\n",
			    algo->name, keylen));
			return 1;
		}
		break;
	default:
		ipseclog((LOG_ERR,
			  "esp_gcm_mature %s: invalid algo %d.\n", sav->alg_enc));
		return 1;
	}

	return 0;
}