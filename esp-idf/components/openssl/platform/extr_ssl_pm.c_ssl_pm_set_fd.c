#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fd; } ;
struct ssl_pm {TYPE_1__ fd; } ;
struct TYPE_5__ {scalar_t__ ssl_pm; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */

void ssl_pm_set_fd(SSL *ssl, int fd, int mode)
{
    struct ssl_pm *ssl_pm = (struct ssl_pm *)ssl->ssl_pm;

    ssl_pm->fd.fd = fd;
}