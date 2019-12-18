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
struct gendisk {int dummy; } ;
struct blk_integrity {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bi_unsupported_name ; 
 struct blk_integrity* blk_get_integrity (struct gendisk*) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 

bool blk_integrity_is_initialized(struct gendisk *disk)
{
	struct blk_integrity *bi = blk_get_integrity(disk);

	return (bi && bi->name && strcmp(bi->name, bi_unsupported_name) != 0);
}