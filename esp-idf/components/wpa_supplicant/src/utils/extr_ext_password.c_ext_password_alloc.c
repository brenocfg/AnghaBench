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

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ mlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

struct wpabuf * ext_password_alloc(size_t len)
{
	struct wpabuf *buf;

	buf = wpabuf_alloc(len);
	if (buf == NULL)
		return NULL;

#ifdef __linux__
	if (mlock(wpabuf_head(buf), wpabuf_len(buf)) < 0) {
		wpa_printf(MSG_ERROR, "EXT PW: mlock failed: %s",
			   strerror(errno));
	}
#endif /* __linux__ */

	return buf;
}