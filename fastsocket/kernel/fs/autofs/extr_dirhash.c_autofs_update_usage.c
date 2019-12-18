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
struct autofs_dirhash {int dummy; } ;
struct autofs_dir_ent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  autofs_delete_usage (struct autofs_dir_ent*) ; 
 int /*<<< orphan*/  autofs_init_usage (struct autofs_dirhash*,struct autofs_dir_ent*) ; 

void autofs_update_usage(struct autofs_dirhash *dh,
			 struct autofs_dir_ent *ent)
{
	autofs_delete_usage(ent);   /* Unlink from current position */
	autofs_init_usage(dh,ent);  /* Relink at queue tail */
}