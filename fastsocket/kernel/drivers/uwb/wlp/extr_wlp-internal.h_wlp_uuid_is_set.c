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
struct wlp_uuid {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (struct wlp_uuid*,struct wlp_uuid*,int) ; 

__attribute__((used)) static inline
int wlp_uuid_is_set(struct wlp_uuid *uuid)
{
	struct wlp_uuid zero_uuid = { .data = { 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00} };

	if (!memcmp(uuid, &zero_uuid, sizeof(*uuid)))
		return 0;
	return 1;
}