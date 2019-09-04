#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {int dh; } ;
typedef  TYPE_2__ LIBSMBContext ;

/* Variables and functions */
 int /*<<< orphan*/  libsmbc_close (TYPE_1__*) ; 
 int /*<<< orphan*/  smbc_closedir (int) ; 

__attribute__((used)) static int libsmbc_close_dir(URLContext *h)
{
    LIBSMBContext *libsmbc = h->priv_data;
    if (libsmbc->dh >= 0) {
        smbc_closedir(libsmbc->dh);
        libsmbc->dh = -1;
    }
    libsmbc_close(h);
    return 0;
}