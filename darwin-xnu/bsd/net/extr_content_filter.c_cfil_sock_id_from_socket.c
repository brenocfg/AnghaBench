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
struct socket {int so_flags; TYPE_1__* so_cfil; } ;
typedef  int /*<<< orphan*/  cfil_sock_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  cfi_sock_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFIL_SOCK_ID_NONE ; 
 int SOF_CONTENT_FILTER ; 

cfil_sock_id_t
cfil_sock_id_from_socket(struct socket *so)
{
	if ((so->so_flags & SOF_CONTENT_FILTER) && so->so_cfil)
		return (so->so_cfil->cfi_sock_id);
	else
		return (CFIL_SOCK_ID_NONE);
}