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
struct wpabuf {int dummy; } ;
struct dh_group {size_t prime_len; int /*<<< orphan*/  prime; int /*<<< orphan*/  generator_len; int /*<<< orphan*/  generator; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ crypto_mod_exp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_mhead (struct wpabuf*) ; 
 scalar_t__* wpabuf_mhead_u8 (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,size_t) ; 

struct wpabuf * 
dh_init(const struct dh_group *dh, struct wpabuf **priv)
{
	struct wpabuf *pv;
	size_t pv_len;

	if (dh == NULL)
		return NULL;

	wpabuf_free(*priv);
	*priv = wpabuf_alloc(dh->prime_len);
	if (*priv == NULL)
		return NULL;

	if (random_get_bytes(wpabuf_put(*priv, dh->prime_len), dh->prime_len))
	{
		wpabuf_free(*priv);
		*priv = NULL;
		return NULL;
	}

	if (os_memcmp(wpabuf_head(*priv), dh->prime, dh->prime_len) > 0) {
		/* Make sure private value is smaller than prime */
		*(wpabuf_mhead_u8(*priv)) = 0;
	}
	wpa_hexdump_buf_key(MSG_DEBUG, "DH: private value", *priv);

	pv_len = dh->prime_len;
	pv = wpabuf_alloc(pv_len);
	if (pv == NULL)
		return NULL;

	if (crypto_mod_exp(dh->generator, dh->generator_len,
						wpabuf_head(*priv), wpabuf_len(*priv),
						dh->prime, dh->prime_len, wpabuf_mhead(pv),
						&pv_len)) {
		wpabuf_free(pv);
		wpa_printf(MSG_INFO, "DH: crypto_mod_exp failed");
		return NULL;
	}
	wpabuf_put(pv, pv_len);
	wpa_hexdump_buf(MSG_DEBUG, "DH: public value", pv);

	return pv;
}