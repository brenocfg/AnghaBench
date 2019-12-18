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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MALLOC_PRINTF_BUFSIZE ; 
 void je_malloc_message (void*,char const*) ; 
 int /*<<< orphan*/  malloc_vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 void wrtmessage (void*,char const*) ; 

void
malloc_vcprintf(void (*write_cb)(void *, const char *), void *cbopaque,
    const char *format, va_list ap)
{
	char buf[MALLOC_PRINTF_BUFSIZE];

	if (write_cb == NULL) {
		/*
		 * The caller did not provide an alternate write_cb callback
		 * function, so use the default one.  malloc_write() is an
		 * inline function, so use malloc_message() directly here.
		 */
		write_cb = (je_malloc_message != NULL) ? je_malloc_message :
		    wrtmessage;
		cbopaque = NULL;
	}

	malloc_vsnprintf(buf, sizeof(buf), format, ap);
	write_cb(cbopaque, buf);
}