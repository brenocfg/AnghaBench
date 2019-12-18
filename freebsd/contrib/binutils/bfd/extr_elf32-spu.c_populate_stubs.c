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
struct stubarr {size_t count; struct spu_stub_hash_entry** sh; } ;
struct spu_stub_hash_entry {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bfd_boolean
populate_stubs (struct bfd_hash_entry *bh, void *inf)
{
  struct stubarr *stubs = inf;

  stubs->sh[--stubs->count] = (struct spu_stub_hash_entry *) bh;
  return TRUE;
}