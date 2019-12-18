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
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,void const*,size_t) ; 

struct wpabuf * wpabuf_alloc_copy(const void *data, size_t len)
{
	struct wpabuf *buf = wpabuf_alloc(len);
	if (buf)
		wpabuf_put_data(buf, data, len);
	return buf;
}