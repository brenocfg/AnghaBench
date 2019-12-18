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
struct mode_data {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  htab_hash_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
hash_mode (const void *p)
{
  const struct mode_data *m = (const struct mode_data *)p;
  return htab_hash_string (m->name);
}