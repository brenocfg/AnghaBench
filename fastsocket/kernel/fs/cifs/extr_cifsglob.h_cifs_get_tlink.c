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
struct tcon_link {int /*<<< orphan*/  tl_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct tcon_link*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct tcon_link *
cifs_get_tlink(struct tcon_link *tlink)
{
	if (tlink && !IS_ERR(tlink))
		atomic_inc(&tlink->tl_count);
	return tlink;
}