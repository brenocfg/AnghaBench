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
struct TYPE_2__ {int features; int /*<<< orphan*/ * ssl; } ;

/* Variables and functions */
 int NOSSL ; 
 int SECURETRANS ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ config ; 

__attribute__((used)) static void
close_connection(int fd)
{
	if (config.ssl != NULL) {
		if (((config.features & SECURETRANS) != 0) &&
		    ((config.features & NOSSL) == 0))
			SSL_shutdown(config.ssl);
		SSL_free(config.ssl);
	}

	close(fd);
}