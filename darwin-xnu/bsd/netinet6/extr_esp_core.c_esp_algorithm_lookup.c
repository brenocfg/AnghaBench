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
struct esp_algorithm {int dummy; } ;

/* Variables and functions */
#define  SADB_EALG_3DESCBC 133 
#define  SADB_EALG_DESCBC 132 
#define  SADB_EALG_NULL 131 
#define  SADB_X_EALG_AES_GCM 130 
#define  SADB_X_EALG_CHACHA20POLY1305 129 
#define  SADB_X_EALG_RIJNDAELCBC 128 
 struct esp_algorithm const aes_cbc ; 
 struct esp_algorithm const aes_gcm ; 
 struct esp_algorithm const chacha_poly ; 
 struct esp_algorithm const des3_cbc ; 
 struct esp_algorithm const des_cbc ; 
 struct esp_algorithm const null_esp ; 

const struct esp_algorithm *
esp_algorithm_lookup(int idx)
{
	switch (idx) {
	case SADB_EALG_DESCBC:
		return &des_cbc;
	case SADB_EALG_3DESCBC:
		return &des3_cbc;
	case SADB_EALG_NULL:
		return &null_esp;
	case SADB_X_EALG_RIJNDAELCBC:
		return &aes_cbc;
	case SADB_X_EALG_AES_GCM:
		return &aes_gcm;
	case SADB_X_EALG_CHACHA20POLY1305:
		return &chacha_poly;
	default:
		return NULL;
	}
}