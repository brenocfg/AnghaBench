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
 int _PAGEMASK ; 
 int _PAGESIZE ; 
 int /*<<< orphan*/  _libctf_debug ; 
 char const* _libctf_zlib ; 
 char* getenv (char*) ; 
 int getpagesize () ; 

void
_libctf_init(void)
{
#ifdef illumos
	const char *p = getenv("LIBCTF_DECOMPRESSOR");

	if (p != NULL)
		_libctf_zlib = p; /* use alternate decompression library */
#endif

	_libctf_debug = getenv("LIBCTF_DEBUG") != NULL;

	_PAGESIZE = getpagesize();
	_PAGEMASK = ~(_PAGESIZE - 1);
}