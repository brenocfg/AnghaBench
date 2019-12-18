#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct fsi_priv {int dummy; } ;
struct TYPE_4__ {TYPE_1__* info; } ;
struct TYPE_3__ {int /*<<< orphan*/  portb_flags; int /*<<< orphan*/  porta_flags; } ;

/* Variables and functions */
 int fsi_is_port_a (struct fsi_priv*) ; 
 TYPE_2__* master ; 

__attribute__((used)) static u32 fsi_get_info_flags(struct fsi_priv *fsi)
{
	int is_porta = fsi_is_port_a(fsi);

	return is_porta ? master->info->porta_flags :
		master->info->portb_flags;
}