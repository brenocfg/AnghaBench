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
struct autofs_dirhash {int /*<<< orphan*/  expiry_head; int /*<<< orphan*/  h; } ;
struct autofs_dir_ent {int dummy; } ;

/* Variables and functions */
 int AUTOFS_HASH_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void autofs_initialize_hash(struct autofs_dirhash *dh) {
	memset(&dh->h, 0, AUTOFS_HASH_SIZE*sizeof(struct autofs_dir_ent *));
	INIT_LIST_HEAD(&dh->expiry_head);
}