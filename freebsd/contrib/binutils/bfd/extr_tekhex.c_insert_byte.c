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
struct data_struct {int* chunk_data; int* chunk_init; } ;
typedef  size_t bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 size_t CHUNK_MASK ; 
 struct data_struct* find_chunk (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
insert_byte (bfd *abfd, int value, bfd_vma addr)
{
  /* Find the chunk that this byte needs and put it in.  */
  struct data_struct *d = find_chunk (abfd, addr);

  d->chunk_data[addr & CHUNK_MASK] = value;
  d->chunk_init[addr & CHUNK_MASK] = 1;
}