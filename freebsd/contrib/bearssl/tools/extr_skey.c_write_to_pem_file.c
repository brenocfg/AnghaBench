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

/* Variables and functions */
 size_t br_pem_encode (void*,void const*,size_t,char const*,int /*<<< orphan*/ ) ; 
 int write_to_file (char const*,void*,size_t) ; 
 int /*<<< orphan*/  xfree (void*) ; 
 void* xmalloc (size_t) ; 

__attribute__((used)) static int
write_to_pem_file(const char *name,
	const void *data, size_t len, const char *banner)
{
	void *pem;
	size_t pemlen;
	int r;

	pemlen = br_pem_encode(NULL, NULL, len, banner, 0);
	pem = xmalloc(pemlen + 1);
	br_pem_encode(pem, data, len, banner, 0);
	r = write_to_file(name, pem, pemlen);
	xfree(pem);
	return r;
}