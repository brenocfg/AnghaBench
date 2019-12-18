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
typedef  int guint64 ;
typedef  int const guint ;
typedef  int* gconstpointer ;

/* Variables and functions */

__attribute__((used)) static guint guint64_hash(gconstpointer _key) {
	const guint64 *key = _key;

	return *key & 0xffffffff;
}