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
struct ar_cache {int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  hashval_t ;
typedef  scalar_t__ PTR ;

/* Variables and functions */

__attribute__((used)) static hashval_t
hash_file_ptr (const PTR p)
{
  return (hashval_t) (((struct ar_cache *) p)->ptr);
}