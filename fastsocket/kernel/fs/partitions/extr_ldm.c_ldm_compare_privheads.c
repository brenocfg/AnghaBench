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
struct privhead {scalar_t__ ver_major; scalar_t__ ver_minor; scalar_t__ logical_disk_start; scalar_t__ logical_disk_size; scalar_t__ config_start; scalar_t__ config_size; int /*<<< orphan*/  disk_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GUID_SIZE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ldm_compare_privheads (const struct privhead *ph1,
				   const struct privhead *ph2)
{
	BUG_ON (!ph1 || !ph2);

	return ((ph1->ver_major          == ph2->ver_major)		&&
		(ph1->ver_minor          == ph2->ver_minor)		&&
		(ph1->logical_disk_start == ph2->logical_disk_start)	&&
		(ph1->logical_disk_size  == ph2->logical_disk_size)	&&
		(ph1->config_start       == ph2->config_start)		&&
		(ph1->config_size        == ph2->config_size)		&&
		!memcmp (ph1->disk_id, ph2->disk_id, GUID_SIZE));
}