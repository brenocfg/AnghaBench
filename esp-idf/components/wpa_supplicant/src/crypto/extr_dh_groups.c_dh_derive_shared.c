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
struct dh_group {size_t prime_len; int /*<<< orphan*/  prime; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ crypto_mod_exp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf_key (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_mhead (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,size_t) ; 

struct wpabuf * 
dh_derive_shared(const struct wpabuf *peer_public,
				 const struct wpabuf *own_private,
				 const struct dh_group *dh)
{
	struct wpabuf *shared;
	size_t shared_len;

	if (dh == NULL || peer_public == NULL || own_private == NULL)
		return NULL;

	shared_len = dh->prime_len;
	shared = wpabuf_alloc(shared_len);
	if (shared == NULL)
		return NULL;

	if (crypto_mod_exp(wpabuf_head(peer_public), wpabuf_len(peer_public),
						wpabuf_head(own_private), wpabuf_len(own_private),
						dh->prime, dh->prime_len,
						wpabuf_mhead(shared), &shared_len)) {
		wpabuf_free(shared);
		wpa_printf(MSG_INFO, "DH: crypto_mod_exp failed");
		return NULL;
	}

	wpabuf_put(shared, shared_len);
	wpa_hexdump_buf_key(MSG_DEBUG, "DH: shared key", shared);

	return shared;
}