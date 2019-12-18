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
struct peer_svc {int dummy; } ;
struct TYPE_2__ {scalar_t__ val_handle; } ;
struct peer_chr {TYPE_1__ chr; } ;

/* Variables and functions */
 scalar_t__ chr_end_handle (struct peer_svc const*,struct peer_chr const*) ; 

int
chr_is_empty(const struct peer_svc *svc, const struct peer_chr *chr)
{
    return chr_end_handle(svc, chr) <= chr->chr.val_handle;
}