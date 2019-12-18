#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  t ;
struct TYPE_3__ {int /*<<< orphan*/  meta; } ;
typedef  TYPE_1__ spiffs_stat ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static time_t vfs_spiffs_get_mtime(const spiffs_stat* s)
{
    time_t t = 0;
#ifdef CONFIG_SPIFFS_USE_MTIME
    memcpy(&t, s->meta, sizeof(t));
#endif
    return t;
}