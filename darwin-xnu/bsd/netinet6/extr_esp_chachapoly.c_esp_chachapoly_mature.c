#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct secasvar {int flags; scalar_t__ alg_enc; TYPE_3__* sah; int /*<<< orphan*/  spi; TYPE_1__* key_enc; } ;
struct esp_algorithm {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {TYPE_2__ saidx; int /*<<< orphan*/  state; int /*<<< orphan*/  dir; int /*<<< orphan*/ * ipsec_if; } ;
struct TYPE_4__ {scalar_t__ sadb_key_bits; } ;

/* Variables and functions */
 scalar_t__ ESP_CHACHAPOLY_KEYBITS_WITH_SALT ; 
 int /*<<< orphan*/  ESP_CHECK_ARG (struct secasvar*) ; 
 scalar_t__ SADB_X_EALG_CHACHA20POLY1305 ; 
 int SADB_X_EXT_DERIV ; 
 int SADB_X_EXT_IIV ; 
 int SADB_X_EXT_OLD ; 
 struct esp_algorithm* esp_algorithm_lookup (scalar_t__) ; 
 int /*<<< orphan*/  esp_log_default (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_err (char*,scalar_t__,...) ; 
 char* if_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

int
esp_chachapoly_mature(struct secasvar *sav)
{
	const struct esp_algorithm *algo;

	ESP_CHECK_ARG(sav);

	if ((sav->flags & SADB_X_EXT_OLD) != 0) {
		esp_log_err("ChaChaPoly is incompatible with SADB_X_EXT_OLD, SPI 0x%08x",
					ntohl(sav->spi));
		return 1;
	}
	if ((sav->flags & SADB_X_EXT_DERIV) != 0) {
		esp_log_err("ChaChaPoly is incompatible with SADB_X_EXT_DERIV, SPI 0x%08x",
					ntohl(sav->spi));
		return 1;
	}

	if (sav->alg_enc != SADB_X_EALG_CHACHA20POLY1305) {
		esp_log_err("ChaChaPoly unsupported algorithm %d, SPI 0x%08x",
					sav->alg_enc, ntohl(sav->spi));
		return 1;
	}

	if (sav->key_enc == NULL) {
		esp_log_err("ChaChaPoly key is missing, SPI 0x%08x",
					ntohl(sav->spi));
		return 1;
	}

	algo = esp_algorithm_lookup(sav->alg_enc);
	if (algo == NULL) {
		esp_log_err("ChaChaPoly lookup failed for algorithm %d, SPI 0x%08x",
					sav->alg_enc, ntohl(sav->spi));
		return 1;
	}

	if (sav->key_enc->sadb_key_bits != ESP_CHACHAPOLY_KEYBITS_WITH_SALT) {
		esp_log_err("ChaChaPoly invalid key length %d bits, SPI 0x%08x",
					sav->key_enc->sadb_key_bits, ntohl(sav->spi));
		return 1;
	}

	esp_log_default("ChaChaPoly Mature SPI 0x%08x%s %s dir %u state %u mode %u",
					ntohl(sav->spi),
					(((sav->flags & SADB_X_EXT_IIV) != 0) ? " IIV" : ""),
					((sav->sah->ipsec_if != NULL) ? if_name(sav->sah->ipsec_if) : "NONE"),
					sav->sah->dir, sav->sah->state, sav->sah->saidx.mode);

	return 0;
}