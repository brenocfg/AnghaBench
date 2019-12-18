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
struct toc_hash_struct {int key_mode; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int rs6000_hash_constant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
toc_hash_function (const void *hash_entry)
{
  const struct toc_hash_struct *thc =
    (const struct toc_hash_struct *) hash_entry;
  return rs6000_hash_constant (thc->key) ^ thc->key_mode;
}